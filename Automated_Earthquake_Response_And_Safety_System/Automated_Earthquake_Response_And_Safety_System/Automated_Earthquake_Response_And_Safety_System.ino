#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal.h>  // Standard LCD library
#include <Servo.h>          // Servo library

// ULTRA SENSITIVE CONFIGURATION
const float ACCEL_THRESHOLD = 0.45;  // A change in acceleration greater than 0.45 m/s² will be considered a potential shake
const unsigned long MIN_EVENT_DURATION = 500;  // Shaking must continue for at least 500 milliseconds to confirm an earthquake.
const unsigned long PEAK_WINDOW = 200;         // If no new shake is detected for 200 milliseconds, the current shaking event is considered over.
const unsigned long COOLDOWN_PERIOD = 10000;    // After an alarm is triggered, the system will remain in alarm state for 10000 milliseconds (10 seconds) before resetting.

// PIN DEFINITIONS 
const int ALARM_LED_PIN = 13;
const int STATUS_LED_PIN = 12;
const int BUZZER_PIN = 11;
const int RELAY_PIN = 10;
const int SERVO_PIN = 9;

// LCD Pins (manual connection)
const int RS = 8;
const int EN = 7;
const int D4 = 6;
const int D5 = 5;
const int D6 = 4;
const int D7 = 3;

// Initialize components
Adafruit_MPU6050 mpu;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
Servo evacuationServo;

// GLOBAL VARIABLES 
unsigned long eventStartTime = 0;     // Declares a global variable to store the time (in milliseconds) when a shaking event started
unsigned long lastPeakTime = 0;       // Declares a global variable to store the time (in milliseconds) of the most recent detected shake
unsigned long alarmTriggeredTime = 0; // Declares a global variable to store the time (in milliseconds) when the alarm was last triggered
bool eventActive = false;             // Declares a global boolean flag to track if a shaking event is currently active. false means no event is happening.
bool alarmTriggered = false;          // Declares a global boolean flag to track if the alarm is currently triggered. false means the alarm is not active.

// Raw acceleration tracking
float lastX = 0, lastY = 0, lastZ = 0;

void setup() {
  // Initialize LEDs and outputs
  pinMode(ALARM_LED_PIN, OUTPUT);
  pinMode(STATUS_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  digitalWrite(ALARM_LED_PIN, LOW);
  digitalWrite(STATUS_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);

  // Initialize servo
  evacuationServo.attach(SERVO_PIN);
  evacuationServo.write(0);  // Close position

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Earthquake");
  lcd.setCursor(0, 1);
  lcd.print("Detector System");
  delay(2000);

  // Initialize sensor with MINIMAL filtering
  if (!mpu.begin()) {
    lcd.clear();
    lcd.print("MPU6050 Error!");
    lcd.setCursor(0, 1);
    lcd.print("Check Wiring");
    while (1) {
      digitalWrite(STATUS_LED_PIN, HIGH);
      delay(500);
      digitalWrite(STATUS_LED_PIN, LOW);
      delay(500);
    }
  }
  
  // MAXIMUM sensitivity settings
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
  
  calibrateSensor();
  
  lcd.clear();
  lcd.print("System Ready");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring...");
  digitalWrite(STATUS_LED_PIN, HIGH);
}

void calibrateSensor() {
  lcd.clear();
  lcd.print("Calibrating...");
  lcd.setCursor(0, 1);
  lcd.print("Keep Still");
  delay(2000);
  
  float sumX = 0, sumY = 0, sumZ = 0;
  int samples = 0;
  
  for (int i = 0; i < 50; i++) {
    sensors_event_t a, g, temp;
    if (mpu.getEvent(&a, &g, &temp)) {
      sumX += a.acceleration.x;
      sumY += a.acceleration.y;
      sumZ += a.acceleration.z;
      samples++;
    }
    delay(10);
  }
  
  lastX = sumX / samples;
  lastY = sumY / samples;
  lastZ = sumZ / samples;
  
  lcd.clear();
  lcd.print("Calib Complete");
  lcd.setCursor(0, 1);
  lcd.print("Baseline Set");
  delay(1000);
}

void updateLCD(String line1, String line2) {
  lcd.clear();
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void activateSafetyProtocols() {
  // Activate buzzer (pulsed)
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
  
  // Activate relay (cut power, activate emergency systems)
  digitalWrite(RELAY_PIN, HIGH);
  
  // Open evacuation path with servo
  evacuationServo.write(90);  // Open position
  
  // Flash alarm LED
  digitalWrite(ALARM_LED_PIN, HIGH);
}

void deactivateSafetyProtocols() {
  // Deactivate all emergency systems
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(ALARM_LED_PIN, LOW);
  
  // Close evacuation path
  evacuationServo.write(0);  // Close position
}

void loop() {
  // Read sensor data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);  // This line fetches the latest data from the MPU6050 sensor, storing the acceleration (a), gyro (g), and temperature (temp) readings.
  
  // Calculate CHANGE in acceleration
  float deltaX = abs(a.acceleration.x - lastX);  // This calculates the absolute difference between the current acceleration on the X-axis and the previous reading stored in lastX
  float deltaY = abs(a.acceleration.y - lastY);  
  float deltaZ = abs(a.acceleration.z - lastZ);
  
  float maxDelta = max(deltaX, max(deltaY, deltaZ));   // This finds the largest change (delta) among the three axes
  
  lastX = a.acceleration.x; // The current acceleration reading is saved into the lastX variable so it can be used as the "previous" value in the next loop cycle
  lastY = a.acceleration.y;
  lastZ = a.acceleration.z;

  // Update LCD display
  static unsigned long lastLCDUpdate = 0;  // The variable is created only once, not every time the function runs.
  if (millis() - lastLCDUpdate >= 300) {   // This section updates the display and LEDs only every 300ms to prevent flickering and make the text readable
    if (alarmTriggered) {
      // Show earthquake warning with countdown
      unsigned long remaining = (COOLDOWN_PERIOD - (millis() - alarmTriggeredTime)) / 1000;   // converts the remaining time for cooldown
      updateLCD("EARTHQUAKE!", "Reset in: " + String(remaining) + "s");
      
      // Flash buzzer during alarm
      static bool buzzerState = false;
      buzzerState = !buzzerState; // toggles the state of the buzzer every time it runs. If the buzzer was ON, it turns it OFF. If it was OFF, it turns it ON. This creates a flashing or beeping effect.
      digitalWrite(BUZZER_PIN, buzzerState);
      
    } else if (eventActive) {  // If a shaking event is in progress but the alarm hasn't been triggered yet, it informs the user
      // Show shaking detection in progress
      updateLCD("Shaking Detected", String(millis() - eventStartTime) + "ms");
      digitalWrite(STATUS_LED_PIN, !digitalRead(STATUS_LED_PIN));         // Blink
      
    } else {   // If the system is in normal, idle monitoring mode, it displays the live, real-time value of maxDelta
      // Normal monitoring mode
      updateLCD("Accel: " + String(maxDelta, 1) + " m/s2", "Ready-Monitoring");
      digitalWrite(STATUS_LED_PIN, HIGH); // Steady on
    }
    lastLCDUpdate = millis();      // updates the time
  }

  // Handle alarm cooldown
  if (alarmTriggered) {
    if (millis() - alarmTriggeredTime >= COOLDOWN_PERIOD) {  // It checks if the alarm has been active for longer than the COOLDOWN_PERIOD
      resetDetector();
    }
    delay(30);
    return;  // If the alarm is active, this return statement exits the loop() function immediately. This means all detection logic below is skipped
  }

  // ULTRA-SENSITIVE DETECTION
  if (maxDelta > ACCEL_THRESHOLD) {  // If the calculated change in acceleration (maxDelta) exceeds the configured threshold 
    lastPeakTime = millis();   // The timer for the "last detected shake" is reset to the current time
    
    if (!eventActive) { //If this is the first shake of a new event, it officially starts the event. It records the start time (eventStartTime), sets the eventActive flag to true, updates the LCD
      eventStartTime = millis();
      eventActive = true;
      updateLCD("Motion Detected","Measuring...");
      digitalWrite(STATUS_LED_PIN, LOW);
    }
    
    // Check if we've had enough sustained motion
    if (eventActive && (millis() - eventStartTime >= MIN_EVENT_DURATION)) { // If an event is already active and it has been going on for longer than MIN_EVENT_DURATION,it immediately calls triggerAlarm().This means the shaking was strong and continuous enough to confirm an earthquake.
      triggerAlarm();
    }
  }
  
  // Check if event should end
  if (eventActive && (millis() - lastPeakTime > PEAK_WINDOW)) {//This checks if an event is active BUT no new shakes have been detected for more than the PEAK_WINDOW
    unsigned long eventDuration = millis() - eventStartTime; // This calculation gives the total length of the event in milliseconds
    
    if (eventDuration >= MIN_EVENT_DURATION) {
      triggerAlarm();
    } else {
      eventActive = false;
      digitalWrite(STATUS_LED_PIN, HIGH);
      updateLCD("Event Too Short", String(eventDuration) + "ms");
      delay(1000);
    }
  }

  delay(10);   //  Pause what you're doing and wait for 10 milliseconds.This is a simple speed limit that keeps the entire system running smoothly and prevents it from going crazy
}

void triggerAlarm() {
  updateLCD("EARTHQUAKE!", "ACTIVATING...");
  delay(500);
  
  // Activate all safety protocols
  activateSafetyProtocols();
  
  // Show confirmation message
  updateLCD("EARTHQUAKE", "CONFIRMED!");
  delay(1000);
  updateLCD("EVACUATE", "IMMEDIATELY!");
  delay(1000);
  updateLCD("POWER CUT", "SAFE EXIT OPEN");
  delay(1000);
  
  alarmTriggered = true;
  alarmTriggeredTime = millis();
  eventActive = false;
  digitalWrite(STATUS_LED_PIN, HIGH);
}

void resetDetector() {
  // Deactivate all safety protocols
  deactivateSafetyProtocols();
  
  eventActive = false;
  alarmTriggered = false;
  
  updateLCD("System Reset", "Monitoring...");
  delay(1000);
}
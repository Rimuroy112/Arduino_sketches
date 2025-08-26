#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <LiquidCrystal.h>  // Standard LCD library
#include <Servo.h>          // Servo library

// ULTRA-SENSITIVE CONFIGURATION
const float ACCEL_THRESHOLD = 0.8;  // Very low threshold
const unsigned long MIN_EVENT_DURATION = 600;  // 600ms of shaking
const unsigned long PEAK_WINDOW = 200;         // 200ms window
const unsigned long COOLDOWN_PERIOD = 10000;    // 2 second cooldown

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
unsigned long eventStartTime = 0;
unsigned long lastPeakTime = 0;
unsigned long alarmTriggeredTime = 0;
bool eventActive = false;
bool alarmTriggered = false;

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
  mpu.getEvent(&a, &g, &temp);
  
  // Calculate CHANGE in acceleration
  float deltaX = abs(a.acceleration.x - lastX);
  float deltaY = abs(a.acceleration.y - lastY);
  float deltaZ = abs(a.acceleration.z - lastZ);
  
  float maxDelta = max(deltaX, max(deltaY, deltaZ));
  
  lastX = a.acceleration.x;
  lastY = a.acceleration.y;
  lastZ = a.acceleration.z;

  // Update LCD display
  static unsigned long lastLCDUpdate = 0;
  if (millis() - lastLCDUpdate >= 300) {
    if (alarmTriggered) {
      // Show earthquake warning with countdown
      unsigned long remaining = (COOLDOWN_PERIOD - (millis() - alarmTriggeredTime)) / 1000;
      updateLCD("EARTHQUAKE!", "Reset in: " + String(remaining) + "s");
      
      // Flash buzzer during alarm
      static bool buzzerState = false;
      buzzerState = !buzzerState;
      digitalWrite(BUZZER_PIN, buzzerState);
      
    } else if (eventActive) {
      // Show shaking detection in progress
      updateLCD("Shaking Detected", String(millis() - eventStartTime) + "ms");
      digitalWrite(STATUS_LED_PIN, !digitalRead(STATUS_LED_PIN)); // Blink
      
    } else {
      // Normal monitoring mode
      updateLCD("Accel: " + String(maxDelta, 1) + " m/s2", "Ready-Monitoring");
      digitalWrite(STATUS_LED_PIN, HIGH); // Steady on
    }
    lastLCDUpdate = millis();
  }

  // Handle alarm cooldown
  if (alarmTriggered) {
    if (millis() - alarmTriggeredTime >= COOLDOWN_PERIOD) {
      resetDetector();
    }
    delay(30);
    return;
  }

  // ULTRA-SENSITIVE DETECTION
  if (maxDelta > ACCEL_THRESHOLD) {
    lastPeakTime = millis();
    
    if (!eventActive) {
      eventStartTime = millis();
      eventActive = true;
      updateLCD("Motion Detected", "Measuring...");
      digitalWrite(STATUS_LED_PIN, LOW);
    }
    
    // Check if we've had enough sustained motion
    if (eventActive && (millis() - eventStartTime >= MIN_EVENT_DURATION)) {
      triggerAlarm();
    }
  }
  
  // Check if event should end
  if (eventActive && (millis() - lastPeakTime > PEAK_WINDOW)) {
    unsigned long eventDuration = millis() - eventStartTime;
    
    if (eventDuration >= MIN_EVENT_DURATION) {
      triggerAlarm();
    } else {
      eventActive = false;
      digitalWrite(STATUS_LED_PIN, HIGH);
      updateLCD("Event Too Short", String(eventDuration) + "ms");
      delay(1000);
    }
  }

  delay(10);
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
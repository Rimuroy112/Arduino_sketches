/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-potentiometer-triggers-piezo-buzzer
 */

// constants won't change
const int POTENTIOMETER_PIN   = A0; // Arduino pin connected to Potentiometer pin
const int BUZZER_PIN          = 3; // Arduino pin connected to Buzzer's pin
const float VOLTAGE_THRESHOLD = 2.5; // Voltages

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT); // set arduino pin to output mode
}

void loop() {
  int analogValue = analogRead(POTENTIOMETER_PIN);      // read the input on analog pin
  float voltage = floatMap(analogValue, 0, 1023, 0, 5); // Rescale to potentiometer's voltage
  Serial.println(voltage);
  if(voltage > VOLTAGE_THRESHOLD)
    digitalWrite(BUZZER_PIN, HIGH); // turn on Piezo Buzzer
  else
    digitalWrite(BUZZER_PIN, LOW);  // turn off Piezo Buzzer
}

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

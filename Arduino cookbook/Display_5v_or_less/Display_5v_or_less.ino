const int referenceVolts = 3.7;
const int batteryPin = 0;
void setup() {
  Serial.begin(9600);

}

void loop() {
  int val = analogRead(batteryPin);      // read the value from the sensor
  float volts = ( val/1023 )*referenceVolts;     // calculate the ratio
  Serial.println(volts);       // print the value in volts

}

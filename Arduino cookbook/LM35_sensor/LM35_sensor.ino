const int inPin = 0;     // analog pin
void setup() {
  Serial.begin(9600);

}

void loop() {
  int value = analogRead(inPin);

  Serial.print(value);
  Serial.print(" > ");
  float millivolts = ( value / 1024.0 ) * 5000;
  float celsius = millivolts / 10;   // sensor output is 10mV per degree celsius
  Serial.print(celsius);
  Serial.print(" degree Celsius, ");

  Serial.print((celsius*9)/5 + 32);     // convert to farenheit
  Serial.println(" degrees Farenheit ");

  delay(1000);           // wait for one second

}

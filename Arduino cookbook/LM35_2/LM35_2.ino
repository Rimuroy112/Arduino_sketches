const int inPin = 0;   // sensor connected to this analog pin
const int outPin = 13;    // digital output pin

const int threshold = 28;    // the degress celsius that will trigger the output pin

void setup() {
  Serial.begin(9600);
  pinMode(outPin, OUTPUT);

}

void loop() {
  int value = analogRead(inPin);
  long celsius = ( value*500L) / 1024;    // 10mV per degree c, see text
  Serial.print(celsius);
  Serial.print(" degree Celsius: ");
  if( celsius > threshold )
  {
    digitalWrite(outPin, HIGH);
    Serial.println("pin is on");
  }
  else 
  {
    digitalWrite(outPin, LOW);
    Serial.println("pin is off");
  }

  delay(1000);    // wait for one second

}

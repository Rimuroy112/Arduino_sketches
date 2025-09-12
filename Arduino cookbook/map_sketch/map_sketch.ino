const int potPin=0;     // select the input pin for the potentiometer
int ledPin=13;          // select the led pin for the led

void setup() {
  pinMode(ledPin, OUTPUT);     // declare the ledpin as an output
  Serial.begin(9600);

}

void loop() {
  int val;               // the value coming from the sensor
  int percent;             // the mapped value

  val = analogRead(potPin);      // read the voltage on the pot( val ranges from 0 to 1023)

  percent = map(val, 0, 1023, 0, 270);    // percent will range from 0 to 100
  digitalWrite(ledPin, HIGH);         // turn the ledpin on
  delay(percent);                   // on  time given by percent value
  digitalWrite(ledPin, LOW);        // turn the ledpin off
  delay(percent);               // off time is 100 minus on time
  Serial.println(percent);          // show the % of pot rotation on serial monitor
}

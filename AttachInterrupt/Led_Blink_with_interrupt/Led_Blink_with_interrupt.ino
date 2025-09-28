
volatile boolean ledOn = false;

void setup() {
  pinMode(2, INPUT);
  pinMode(7, OUTPUT);
  attachInterrupt(0,buttonPressed, RISING);

}

void loop() {
  

}
void buttonPressed()
{
  if(ledOn)
  {
    ledOn = false;
    digitalWrite(7, LOW);
  }
  else
  {
    ledOn = true;
    digitalWrite(7,HIGH);
  }
}

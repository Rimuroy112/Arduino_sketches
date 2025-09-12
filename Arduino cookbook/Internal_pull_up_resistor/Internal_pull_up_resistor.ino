const int LEDpin = 8;       // choose the pin for led
const int INPUTpin = 7;      // choose the input pin for switch
void setup() {
  pinMode(LEDpin, OUTPUT);    //  led for output
  pinMode(INPUTpin, INPUT);   // switch as input  


}

void loop() {
  int val = digitalRead(INPUTpin);   // read the input value
  if( val == HIGH)                   // check if button is pressed
  {
    digitalWrite(LEDpin, HIGH);      // led is on
  }
  else
  {
     digitalWrite(LEDpin, LOW);      // led is off
  }
 
 }

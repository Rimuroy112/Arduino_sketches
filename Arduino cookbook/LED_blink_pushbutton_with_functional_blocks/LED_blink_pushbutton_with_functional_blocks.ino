const int ledpin = 13;       //output pin for the LED
const int inputpin = 2;      // input pin for the switch
void setup() {
 pinMode(ledpin, OUTPUT);
 pinMode(inputpin, INPUT);
 pinMode(inputpin, HIGH);      // use external pull-up resistor
 Serial.begin(9600); 

}

void loop() {
  Serial.println("Press and hold the switch to stop blinking:");
  int count = blink3(250);       // blink the led 250ms on and 250ms off
  Serial.print("The number of times the LED blinked was :");
  Serial.println(count); 

}
// blink an led using the given delay period
// return the number of times the led flashed
int blink3(int period)
{
  int result = 0;
  int switchVal = HIGH;    // with pull-ups, this will be HIGH when switch is up
  while(switchVal == HIGH)    // repeat this loop until switch is pressed
  {
   digitalWrite(13, HIGH);
   delay(period);
   digitalWrite(13, LOW);
   delay(period);
   result = result + 1;        // increment the count
   switchVal = digitalRead(inputpin);  // read input value
  }
  // here when switchVal is no longer HIGH because the swtich is pressed
  
  return result;        // this value will be returned
}                               

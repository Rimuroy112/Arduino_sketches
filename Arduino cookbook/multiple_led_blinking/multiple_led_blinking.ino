const int firstLedPin = 3;    
const int secondLedPin = 5;           // choose the pin for each fo the leds
const int thirdLedPin = 6;
void setup() {
  pinMode(firstLedPin, OUTPUT);
  pinMode(secondLedPin, OUTPUT);      // declare led pin as output
  pinMode(thirdLedPin, OUTPUT);     

}

void loop() {
  // flash each of the leds for 1000 milliseconds ( 1 second )
  blinkLED(firstLedPin, 1000);
  blinkLED(secondLedPin, 1000);
  blinkLED(thirdLedPin, 1000);

}
// blink the led on the given pin for the duration in milliseconds
void blinkLED(int pin, int duration)
{
  digitalWrite(pin, HIGH);
  delay(duration);          // turn the led on
  digitalWrite(pin, LOW);
  delay(duration);          // turn the led off
}

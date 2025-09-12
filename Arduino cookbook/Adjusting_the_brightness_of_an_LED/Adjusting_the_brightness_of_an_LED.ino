const int firstLed = 3;
const int secondLed = 5;      // specify the pin for each of the leds

int brightness = 0;
int increment = 1;
void setup() {
  // pins driven by analogWrite do not need to be declared as outputs

}

void loop() {
if( brightness > 255 )
{
  increment = -1;       // count down after reaching 255
}
else if(brightness < 1 )
{
  increment = 1;       // count down after dropping back down to 0
}
brightness = brightness + increment;     // increment

// write the brightness value to the LEDS
analogWrite(firstLed, brightness);
analogWrite(secondLed, brightness);
delay(10);             // 10ms for each step change means 2.55 secs fo fade up or down
}

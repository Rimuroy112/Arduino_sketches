int dataPin = 4;    // SER
int latchPin = 5;   // RCLK
int clockPin = 6;   // SRCLK


byte leds = 0;      // variable to hold the pattern of which leds are currently turned on or off


void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

}

void loop() {
  leds = 0;       //Initially turns all the LEDs off
  updateShiftRegister();
  delay(500);
  for(int i = 0; i<8; i++)  // turns all the leds on one by one
  {
    bitSet(leds, i);      // Set the bit that controls that LEd in the variable 'leds'
    updateShiftRegister();
    delay(100);
  }

}

void updateShiftRegister() // This function sets the latchPin to low, then calls the Arduino
{                           //function 'shiftOut' to shift out contents of variable 'leds'
                             // in the shift register before putting the 'latchPin' high again.
digitalWrite(latchPin, LOW);
shiftOut(dataPin, clockPin, MSBFIRST, leds);
digitalWrite(latchPin, HIGH);
 
}
                          

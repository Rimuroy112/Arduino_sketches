int outputEnablePin = 3;   // OE
int dataPin = 4;          // SER
int latchPin = 5;         // RCLK
int clockPin = 6;         // SRCLK

byte leds = 0;

void setup() {
pinMode(dataPin, OUTPUT);
pinMode(latchPin, OUTPUT);
pinMode(clockPin, OUTPUT);
pinMode(outputEnablePin, OUTPUT);


}

void loop() {
setBrightness(255);
leds = 0;
updateShiftRegister();
delay(100);
for(int i = 0; i<8; i++)
{
  bitSet(leds, i);
  updateShiftRegister();
  delay(100);
  
}
for(byte b = 255; b>0; b--)
{
  setBrightness(b);
  delay(10);
 }
}

void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}

void setBrightness(byte brightness)
{
  analogWrite(outputEnablePin, 255-brightness);
}

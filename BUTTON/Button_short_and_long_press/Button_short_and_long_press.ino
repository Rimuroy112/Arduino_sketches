#define button 6
#define led 7

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
  byte r = push(button);
  if(r)
  {
    if(r == 1) Serial.println("Short pressed!");
    else if(r == 2) Serial.println("Long pressed!");
  }

}

byte push(byte button_number)
{
  uint32_t b_timer = 0;
  if(!digitalRead(button_number))  // if button is pressed
  {
    delay(50);    // debounce delay
    while(!digitalRead(button_number))
    {
      delay(50);
      b_timer += 50;
      if(b_timer > 1000) digitalWrite(led,1);
    }
    digitalWrite(led,0);
    if(b_timer > 1000) return 2;
    else if(b_timer > 0) return 1;
  }
  return 0;
}

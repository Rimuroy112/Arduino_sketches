const int btn_pin = 8;
const int led_pin = 6;
int i;
void setup() {
 pinMode(btn_pin, INPUT_PULLUP);
 pinMode(led_pin, OUTPUT);

}

void loop() {
  i = 0;
  while(i < 256)
  {
    analogWrite(led_pin, i);
    if(digitalRead(btn_pin)== LOW)
    {
     continue;
    }
    i++;
    delay(5);
  }
  
}

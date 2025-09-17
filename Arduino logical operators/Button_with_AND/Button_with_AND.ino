const int btn_pin = 8;
const int led_pin = 6;
int btn_prev = HIGH;
int btn_state;
void setup() {
  pinMode(btn_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);

}

void loop() {
  btn_state = digitalRead(btn_pin);
  if((btn_state == LOW) && (btn_prev == HIGH))
  {
    digitalWrite(led_pin, HIGH);
    delay(300);
    digitalWrite(led_pin, LOW);
  }
  btn_prev = btn_state;

}

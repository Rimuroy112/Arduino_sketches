#define left 6
#define right 8
int value = 0;
bool flag_l = 0, flag_r = 0;

void setup() {
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  Serial.begin(9600);
}
void loop() {
  if (!digitalRead(left)) {
    flag_l = cont_push(left, flag_l);
    value--;
    Serial.println(value);
  }
  if (!digitalRead(right)) {
    flag_r = cont_push(right, flag_r);
    value++;
    Serial.println(value);
  }
}
bool cont_push(byte button_number, bool indicator) {
  delay(50);  //debounce delay
  uint32_t b_timer = millis();
  while (!digitalRead(button_number))
    if (millis() - b_timer > 1000 || indicator) return 1;
  delay(50);  //debounce delay
  return 0;
}

float deg = 30;
float rad = deg*DEG_TO_RAD;
void setup() {
  Serial.begin(9600);
 
}

void loop() {
  Serial.println(rad);
  Serial.println(sin(rad));
  Serial.println(cos(rad));
  delay(500);

}

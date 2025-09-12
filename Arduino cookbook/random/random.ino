long randNumber;

void setup() {
  Serial.begin(9600);
 
}

void loop() {
  randNumber = random(300);
  Serial.println(randNumber);
  delay(500);
}

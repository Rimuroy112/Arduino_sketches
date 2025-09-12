const int sensorPin = 2;
const int buzzerPin = 13;
void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

}

void loop() {
  int val = digitalRead(sensorPin);
  if(val==HIGH)
  {
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    
  }
  
  
}

const int buzzer = 3;
const int pot = A0;
const int Threshold = 500;


void setup() {
  pinMode(buzzer, OUTPUT);

}

void loop() {
  int analogValue = analogRead(pot);
  if(analogValue > Threshold )
   digitalWrite(buzzer, HIGH);
  else 
   digitalWrite(buzzer, LOW);

}

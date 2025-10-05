const int trig = 6;
const int echo = 7;
const int buzzer = 3;
const int Threshold = 20;

float distance,duration;

void setup() {
Serial.begin(9600);
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
pinMode(buzzer, OUTPUT);  

}

void loop() {
  // generate 10 microsecond pulse to trig pin
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // measure duration of pulse from echo pin
  duration = pulseIn(echo, HIGH);
  distance = (0.017*duration);

  if(distance < Threshold)
   digitalWrite(buzzer, HIGH);
   else
   digitalWrite(buzzer, LOW);

   Serial.print("Distance: ");
   Serial.print(distance);
   Serial.println(" cm");

}

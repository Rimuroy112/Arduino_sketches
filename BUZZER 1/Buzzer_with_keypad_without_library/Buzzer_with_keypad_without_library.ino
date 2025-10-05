#define r0 2
#define r1 3 
#define r2 4
#define r3 5
#define c0 6
#define c1 7
#define c2 8
#define c3 9
#define buzzer 10
void setup() {
  Serial.begin(9600);
  pinMode(c0, INPUT_PULLUP);
  pinMode(c1, INPUT_PULLUP);
  pinMode(c2, INPUT_PULLUP);
  pinMode(c3, INPUT_PULLUP);
  pinMode(r0, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  digitalWrite(r0, LOW);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, HIGH);
  if(digitalRead(c0) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 119;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
  else if(digitalRead(c1) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 106;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
  else if(digitalRead(c2) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 94;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
  else if(digitalRead(c3) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 89;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
  digitalWrite(r0, HIGH);
  digitalWrite(r1, LOW);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, HIGH);
   if(digitalRead(c0) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 79;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
  else if(digitalRead(c1) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 71;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
   else if(digitalRead(c2) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 63;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
  else if(digitalRead(c3) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 119;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
   digitalWrite(r0, HIGH);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, LOW);
  digitalWrite(r3, HIGH);
   if(digitalRead(c0) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 25;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
  else if(digitalRead(c1) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 20;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
   else if(digitalRead(c2) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 10;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
  else if(digitalRead(c3) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 50;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
   digitalWrite(r0, HIGH);
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, LOW);
   if(digitalRead(c0) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 50;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
  else if(digitalRead(c1) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 50;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
   else if(digitalRead(c2) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 50;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }
  else if(digitalRead(c3) == LOW)
  {
    TCCR2A = B01000011;
    TCCR2B = B00001110;
    OCR2A = 50;
    delay(100);
    TCCR2B = B00001000;
    TCCR2A = B00000000;
    digitalWrite(10, LOW);
  }

}

int Button = 7;
int Buzzer = 3;

void setup() {
  pinMode(Buzzer, OUTPUT);
  pinMode(Button, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
 int buttonState = digitalRead(Button);

 if(buttonState == LOW)
 {
  Serial.println("The button is pressed !");
  digitalWrite(Buzzer, HIGH);
  
 }
 else
 {
 Serial.println("The button is not pressed !");
  digitalWrite(Buzzer, LOW);
  
 }

}

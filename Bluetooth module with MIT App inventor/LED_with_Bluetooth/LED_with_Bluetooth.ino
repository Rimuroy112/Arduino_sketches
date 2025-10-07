const int led = 9;
int receive = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

}

void loop() {
  if(Serial.available() > 0)
  {
    receive = Serial.read();
    Serial.println(receive);
    if(receive == '1')
  {
    digitalWrite(led, HIGH);
  }
  else if(receive == '0')
  {
    digitalWrite(led, LOW);
  }
  }
  
}

const int light1 = 9;
const int light2 = 10;
int received = 0;
int light_state = 0;

void setup() {

  Serial.begin(9600);
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);

}

void loop() {
 if(Serial.available() > 0)
 {
  received = Serial.read();
 }
 
 
 if(light_state == 0 && received == 'a')
 {
  digitalWrite(light1, HIGH);
  light_state = 1;
  received = 0;
 }
 if(light_state == 1 && received == 'a')
 {
  digitalWrite(light1, LOW);
  light_state == 0;
  received = 0;
 }

 if(light_state == 0 && received == 'b')
 {
  digitalWrite(light2, HIGH);
  light_state = 1;
  received = 0;
 }
 if(light_state == 1 && received == 'b')
 {
  digitalWrite(light2, LOW);
  light_state == 0;
  received = 0;
 }
}

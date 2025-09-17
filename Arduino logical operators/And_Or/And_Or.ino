void setup() {
  Serial.begin(9600);
  int a = 2;
  int b = 9;
  if( (a == 2) && (b < 10) )
  {
    Serial.println("True");
  }
  else{
    Serial.println("False");
  }
  if( !(a < 1) || (b >= 10) )
  {
    Serial.println("True");
  }
  else{
    Serial.println("False");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}

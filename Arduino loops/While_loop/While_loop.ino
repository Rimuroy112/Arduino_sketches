int i;
void setup() {
  Serial.begin(9600);
  i = 0;
  while(i<3)
  {
    Serial.println("Hello");
    i = i+1;
  }
  Serial.print("Done !");

}

void loop() {
  // put your main code here, to run repeatedly:

}

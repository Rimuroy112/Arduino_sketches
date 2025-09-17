int i;
void setup() {
  Serial.begin(9600);
  i = 0;
  for(i= 0; i<3; i++)
  {
    Serial.println("Hello");
  }
  Serial.print("Done!");
}

void loop() {
  // put your main code here, to run repeatedly:

}

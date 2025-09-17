int i;
void setup() {
  Serial.begin(9600);
  i = 0;
  do{
    Serial.println("Hello");
    i = i + 1;
  }while(i<0);
  Serial.println("Done");
}

void loop() {
  // put your main code here, to run repeatedly:

}

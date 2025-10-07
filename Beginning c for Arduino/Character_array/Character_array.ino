void setup() {
  Serial.begin(9600);
  char firstName[]="Rimu";
  char lastName[]=" roy";
  strcat(firstName, lastName);
  Serial.print(firstName);

}

void loop() {
  // put your main code here, to run repeatedly:

}

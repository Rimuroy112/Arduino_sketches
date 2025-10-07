void setup() {
  int k;
  Serial.begin(9600);
  for(k=0, Serial.print("Exp 1:"),Serial.println(k); // expression 1
  k<10,Serial.print("Exp 2:"),Serial.println(k);    // expression 2
  k++,Serial.print("Exp 3:"),Serial.println(k))    // expression 3
  {
  Serial.print("In loop body K squared :");
  Serial.println(k * k);
  delay(1000);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}

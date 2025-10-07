void setup() {
  Serial.begin(9600);
  Serial.println("Enter a letter between A-F ");

}

void loop() {
  char C;
  while(true)
  {
  if(Serial.available()>0)
  {
    C = Serial.read();
    C = toupper(C);
    switch(C)
    {
      case 'A':
        Serial.println("Congratulations ! you are doing great job ");
        break;
      case 'B':
        Serial.println("Good ");
        break;
      case 'C':
        Serial.println("You passed !");
        break;
      case 'D':
        Serial.println("You are on the edge ");
        break;
      case 'F':
        Serial.println("See you next semester ");
        break;
       default:
        Serial.println("Someting went wrong ");
        break;
        
        
    }
  }
 }

}

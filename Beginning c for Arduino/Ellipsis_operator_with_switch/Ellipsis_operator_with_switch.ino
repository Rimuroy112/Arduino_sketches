void setup() {
  Serial.begin(9600);
  Serial.println("Enter the grade of your exam: ");

}

void loop() {

  char letterGrade;
  int grade;
  if(Serial.available()>0)
  {
    switch(grade)
    {
      case 0 ... 59:
       {
        letterGrade = 'F';
        Serial.println(letterGrade);
        
       }
       break;
        case 60 ... 69:
       {
        letterGrade = 'D';
        Serial.println(letterGrade);
       
       }
        break;
        case 70 ... 79:
       {
        letterGrade = 'C';
        Serial.println(letterGrade);
       
       }
        break;
        case 80 ... 89:
       {
        letterGrade = 'B';
        Serial.println(letterGrade);
      
       }
         break;
        case 90 ... 99:
       {
        letterGrade = 'A';
        Serial.println(letterGrade);
      
       }
         break;
    }
  }
 
}

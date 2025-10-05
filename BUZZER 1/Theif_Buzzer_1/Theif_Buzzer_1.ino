int PIRsensor = 4;
int buzzer= 8;
int theif=0;
void setup() 
{
  pinMode(PIRsensor,INPUT); //declare sensor as input
  pinMode(buzzer,OUTPUT); //declare as output
  

}

void loop() 
{
  theif=digitalRead(PIRsensor);
  if(theif==1)
  {
    digitalWrite(buzzer, HIGH);
    delay(2000);
    digitalWrite(buzzer,LOW);
    delay(1000);
  
  }
  else
  { digitalWrite(buzzer,LOW);
  }

}

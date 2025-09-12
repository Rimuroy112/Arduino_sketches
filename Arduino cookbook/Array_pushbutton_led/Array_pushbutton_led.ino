int inputPins[] = { 2,3,4 } ;         // create  an array for inputPins as switches
int ledPins[] = { 10, 11, 12 } ;       // create an array for ledPins
void setup() {
  for ( int index=0; index<4; index++)
  {
    pinMode(inputPins[index], INPUT);   //declare switch as input
    pinMode(ledPins[index], OUTPUT);     //declare led as output 
    digitalWrite(inputPins[index], HIGH);   //enable pull-up resistor
  }
  

}

void loop() {
  for( int index=0; index<4; index++)
  {
   int val = digitalRead(inputPins[index]);   // read input value
   if(val == LOW )                           // check if button is pressed
   {
     digitalWrite(ledPins[index],HIGH);        // led is on
   }
   else
   {
     digitalWrite(ledPins[index],LOW);
   }
  }
  
  
  
  

}

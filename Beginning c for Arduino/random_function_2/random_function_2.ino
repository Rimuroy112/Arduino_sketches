#define MAX 5000L
#define MIN 0L
#define TARGETVALUE 2500L

#define MAXRECYCLES 5
#define FOUNDITIOPIN 10    // use the green LED
#define RECYCLEIOPIN 11    // use the red LED
#define PAUSE 1000

int foundIt = FOUNDITIOPIN;
int recycle = RECYCLEIOPIN;
long randomNumber;
int recycleCounter = 0;
int counter = 0;

void setup() {

  Serial.begin(9600);
  pinMode(foundIt, OUTPUT);
  pinMode(recycle, OUTPUT);
  randomSeed(analogRead(A0));   // this seeds the random number generator

}

void loop() {
  while(counter != -1)      // check for negative values
  {
    randomNumber = generateRandomNumber();
    if( randomNumber == TARGETVALUE )
    {
      Serial.print("Counter = ");
      Serial.print(counter, DEC);
      Serial.print("  recycleCounter = ");
      Serial.println(recycleCounter, DEC);
      digitalWrite(foundIt, HIGH);
      delay(PAUSE);
      digitalWrite(foundIt, LOW);
    }

    counter++;
    if(counter < 0)                 // we have overflowed an int
    {
      counter = 0;
      recycleCounter++;
      Serial.print("recycleCounter =");
      Serial.println(recycleCounter, DEC);
      digitalWrite(recycle, HIGH);
      delay(PAUSE);
      digitalWrite(recycle, LOW);
      
    }
    if(recycleCounter == MAXRECYCLES)
    {
      FakeAnEnd();        // end program
    }
  }

}

long generateRandomNumber()
{
  return random(MIN, MAX);
}

void FakeAnEnd()       // fake the end of the program
{
  while(true)
  {
    ;
  }
}

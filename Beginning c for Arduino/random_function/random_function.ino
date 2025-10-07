#define HEADIOPIN 11
#define TAILIOPIN 10

#define PAUSE 50

int headsCounter;
int tailsCounter;       // heads / tails counters

long loopCounter;
long randomNumber = 0L;    // 'L' tells the compiler it's a long data type not an int

void setup() {
  Serial.begin(115200);
  headsCounter = 0;
  tailsCounter = 0;
  loopCounter = 0;

  pinMode(HEADIOPIN, OUTPUT);
  pinMode(TAILIOPIN, OUTPUT);
  randomSeed(analogRead(A0));     // this seeds the random number generator
}

void loop() {
  randomNumber = generateRandomNumber();
  digitalWrite(HEADIOPIN, LOW);
  digitalWrite(TAILIOPIN, LOW);
  delay(PAUSE);

  if(randomNumber % 2==1)
  {
    digitalWrite(HEADIOPIN, HIGH);
    headsCounter++;
  }
  else
  {
    digitalWrite(TAILIOPIN, HIGH);
    tailsCounter++;
  }
  loopCounter++;
  if(loopCounter % 100 == 0)
  {
    Serial.print("After ");
    Serial.print(loopCounter);
    Serial.print(" Coin flips, heads: ");
    Serial.print(headsCounter);
    Serial.print(" and tails: ");
    Serial.println(tailsCounter);
  }
delay(PAUSE);
}

long generateRandomNumber()
{
  return random(0, 1000000);
}

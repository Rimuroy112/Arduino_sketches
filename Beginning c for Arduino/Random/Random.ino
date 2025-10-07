#define HEAD 11
#define TAIL 10

int headCount;
int tailCount;
long loopCount;
long randomNumber = 0L;

void setup() {
  Serial.begin(115200);
  pinMode(HEAD, OUTPUT);
  pinMode(TAIL, OUTPUT);
  randomSeed(analogRead(A0));    // this seeds the random number generator
  

}

void loop() {
  randomNumber = randomNumberGenerator();
  digitalWrite(HEAD, LOW);
  digitalWrite(TAIL, LOW);
  delay(50);

  if(randomNumber % 2 == 1)
  {
    digitalWrite(HEAD, HIGH);
    headCount++;
  }
  else
  {
    digitalWrite(TAIL, HIGH);
    tailCount++;
  }
  loopCount++;
  if(loopCount % 100 == 0);
  {
    Serial.print("After ");
    Serial.print(loopCount);
    Serial.print(" coin flips, heads: ");
    Serial.print(headCount);
    Serial.print(", tails: ");
    Serial.println(tailCount);
  }
  delay(50);

}
long randomNumberGenerator()
{
  return random(0, 1000000);
}

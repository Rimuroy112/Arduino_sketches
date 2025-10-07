#define LED LED_BUILTIN
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

}

void loop() {
  int counter;
  for(counter=0; counter<1000; counter++)
  {
    if(counter%2==0)
    digitalWrite(LED, HIGH);
    else
    digitalWrite(LED, LOW);

    Serial.println(counter);
    delay(500);
  }

}

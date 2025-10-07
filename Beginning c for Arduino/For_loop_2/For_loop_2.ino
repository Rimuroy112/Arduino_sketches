#define MAXLOOP 10
void setup() {
  int squares[MAXLOOP];
  int counter;
  Serial.begin(9600);

  // construct the list
  for(counter=0; counter<MAXLOOP; counter++)
  {
    squares[counter]= counter * counter;
  }

  // display the list
  for(counter=0; counter<MAXLOOP; counter++)
  {
    Serial.println(squares[counter]);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}

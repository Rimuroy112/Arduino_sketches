const int ledPin = 13;        // the number of the output pin
const int inPin = 2;          // the number of the input pin


const int debounceTime = 20;           // the time in milliseconds required for the switch to be stable
const int fastIncrement = 1000;        // increment faster after this many milliseconds
const int veryFastIncrement = 4000;      // and increment even faster after this many milliseconds

int count = 0;

void setup() {
  pinMode(inPin, INPUT);
  digitalWrite(inPin, HIGH);     //turn on pull-up resistor
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  int duration  = switchTime();
  if(duration > veryFastIncrement)
  count = count + 10;
  else if(duration > fastIncrement)
  count = count + 4;
  else if(duration > debounceTime)
  count = count + 1;

  else
  { 
    // switch not pressed so service the timer
    if(count == 0)
    digitalWrite(ledPin, HIGH);    // turn the led on if the count is 0
    else
    {
      digitalWrite(ledPin, LOW);    // turn the led off if the count is not 0
     count = count -1;
    }
  }
   Serial.println(count);
   delay(100);
} 
    // return the time in milliseconds that the switch has been in pressed (LOW)
 long switchTime()

    // these variables are static
    static unsigned long startTime = 0;   // the time the switch state change was first detected
    static boolean state;                 // the current state of the switch
   if(digitalRead(inPin) != state)       // check to see if the switch has changed state
    {
      state = ! state;      // yes, invert the state
      startTime = millis();     // store the time
    } 
    if(state == LOW)
    return millis() - startTime;    // switch pushed, return time in milliseconds
    else
    return 0;    // return 0 if the switch is not pushed

}

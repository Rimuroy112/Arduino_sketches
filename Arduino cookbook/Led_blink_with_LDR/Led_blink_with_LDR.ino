const int ledPin = 9;      // led pin connected to digital pin 9
const int sensorPin = A0;    // sensorPin connected to analog pin A0

//the next two lines set the minimum and maximum delays between blink

const int minimumduration = 100;    //minimum delay between blink
const int maximumduration = 1000;   //maximum delay between blink

void setup() {
  pinMode(ledPin, OUTPUT);      //set the led pin for output
  Serial.begin(9600);        //initialize the serial communication

}

void loop() 
{
  int rate = analogRead(sensorPin);          //read the analog input
  
  //the next line scales the delay between minimum and maximum value
  
  rate = map(rate, 200, 800, minimumduration,maximumduration);       //map the blink delay
  rate = rate / 5;
  Serial.println(rate);           // print rate to serial monitor
  digitalWrite(ledPin, HIGH);      // led pin on
  delay(rate);                    // wait duration on light level
  digitalWrite(ledPin, LOW);      // led pin off
  delay(rate);
  

}

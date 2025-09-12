float value = 1.1;
void setup()
{
Serial.begin(9600);
}
void loop()
{
value = value - 0.1; // reduce value by 0.1 each time through the loop
if( value == 0)
Serial.println("The value is exactly zero");
else if(fabs(value) < .0001) // function to take the absolute value of a float
Serial.println("The value is close enough to zero");
else
Serial.println(value);
delay(500);
}

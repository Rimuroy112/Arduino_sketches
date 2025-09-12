#include <Keypad.h>    // keypad library

const int numRows = 4;       // num of rows in the keypad
const int numCols = 4;       // num of columns
const int debounceTime = 20;   // number of milliseconds for switch to be stable

// keymap defines the character returned when the corresponding key is pressed

const char keymap[numRows][numCols]=
{
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'c' },
  { '*', '0', '#', 'D' }
  
};

// this array determines the pins used for rows and columns
const int rowPins[numRows] = { 2,3,4,5 };    // rows 0 through 3
const int colPins[numCols] = { 6,7,8,9 };    // cols 0 through 3


void setup() {
  Serial.begin(9600);
  for(int row = 0; row < numRows; row++)
  {
    pinMode(rowPins[row], INPUT);            //  Set row pins as input
    digitalWrite(rowPins[row], HIGH);        // turn on Pull-ups
    
  }
  for(int column = 0; column < numRows; column++)
  {
    pinMode(colPins[column], OUTPUT);            //  Set column pins as output
    digitalWrite(colPins[column], HIGH);        //  make all columns inactive
    
  }

}

void loop() {
  char key = getKey();                 // if the character is not 0 then its a valid key press
  if( key != 0)
  {
    Serial.print("Got key");
    Serial.println(key);
 }
}

// returns with the key pressed , or 0 if no key is pressed
char getKey()
{
  char key=0;              // 0 indicates no key pressed
  for(int column = 0; column < numCols; column++)
  {
    digitalWrite(colPins[column], LOW);        // active the current column
    for(int row = 0; row < numRows; row++)       // scan all rows for a key press
    
    {
      if(digitalRead (rowPins[row]) == LOW)        // Is a key pressed
      {
        delay(debounceTime);                        // debounce
        while(digitalRead(rowPins[row])  == LOW); 
                                                   // wait for key to be released
        key = keymap[row][column];                  // remember which key was pressed
      }
    }
    digitalWrite(colPins[column], HIGH);          // deactive the current column
    
  }
  return key;        // returns the key pressed or 0 if none
}

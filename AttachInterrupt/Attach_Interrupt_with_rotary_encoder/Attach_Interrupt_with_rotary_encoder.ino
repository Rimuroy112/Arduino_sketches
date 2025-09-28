#include <LiquidCrystal.h>
LiquidCrystal lcd(3,4,5,6,7,8);

// Rotary Encoder Inputs
#define CLK 2
#define DT 3

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";

void setup() {
  lcd.begin(16,2);
  
  // Set encoder pins as inputs
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);
  
  // Call updateEncoder() when any high/low changed seen
  // on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
  lcd.setCursor(0,0);
  lcd.write("Rotary Encoder ");
  lcd.setCursor(0,1);
  lcd.write("AttachInterrupt!");
  delay(3000);
  lcd.clear();
}

void loop() {
  //Do some useful stuff here
}

void updateEncoder(){
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(DT) != currentStateCLK) {
      counter ++;
      currentDir ="CW";
    } else {
      // Encoder is rotating CW so increment
      counter --;
      currentDir ="CCW";
    }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Direction ");
    lcd.setCursor(10,0);
    lcd.print(currentDir);
    lcd.setCursor(0,1);
    lcd.print("Counter: ");
    lcd.setCursor(8,1);
    lcd.print(counter);

  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;
}

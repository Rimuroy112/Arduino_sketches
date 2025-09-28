#include <LiquidCrystal.h>
LiquidCrystal lcd(4,5,6,7,8,9);
volatile int output = LOW;
const int Led = 10;
int i = 0;


void setup() {
  
pinMode(Led, OUTPUT);
lcd.begin(16,2);
lcd.setCursor(0,0);
lcd.print("ArduinoInterrupt");
lcd.setCursor(0,1);
lcd.print("Project");
delay(3000);
lcd.clear();
attachInterrupt(digitalPinToInterrupt(2),buttonPressed1, RISING);
attachInterrupt(digitalPinToInterrupt(3),buttonPressed2, RISING);

}

void loop() {
  lcd.clear();
  lcd.print("COUNTER:");
  lcd.print(i);
  i++;
  delay(1000);
  digitalWrite(Led, output);
  

}
void buttonPressed1()
{
  output = LOW;
  lcd.setCursor(0,1);
  lcd.print("Interrupt 1");
  
}

void buttonPressed2()
{
  output = HIGH;
  lcd.setCursor(0,1);
  lcd.print("Interrupt 2");
}

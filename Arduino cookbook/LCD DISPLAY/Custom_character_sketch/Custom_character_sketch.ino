
// include the library code
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte happy[8] =
{
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};


byte saddy[8] =
{
  B00000,
  B10001,
  B00000,
  B00000,
  B01110,
  B10001,
  B00000,
  B00000
};

void setup() {
  lcd.createChar(0, happy);
  lcd.createChar(1, saddy);
  lcd.begin(16, 2);

}

void loop() {
  for(int i=0; i<2; i++)
  {
    if(i == 0){
       lcd.setCursor(0, 0);
    lcd.write(i);
    delay(500);
      
    }
    if(i== 1){
          lcd.setCursor(0, 1);
    lcd.write(i);
    delay(500);
      
    }
    lcd.clear();
   

  }

}

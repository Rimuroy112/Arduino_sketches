#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
#define buzzer 9
#define led 8
#define button 10
int state = 0;

int xSample = 0,ySample = 0, zSample = 0;
int buz = 0;
int start = 0;
#define samples 20
#define maxVal 20  // maximum change
#define minVal -20  // minimum change
#define buzTime 5000 // buzzer on time


void setup() {
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(buzzer, LOW);
  digitalWrite(led, LOW);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("EarthQuake ");
  lcd.setCursor(0,1);
  lcd.print("Detector !");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calibration");
  lcd.setCursor(0,1);
  lcd.print("Start !");
  digitalWrite(led, HIGH);
  for(int i=0; i<samples; i++)
  {
    xSample +=analogRead(A0);
    ySample +=analogRead(A1);
    zSample +=analogRead(A2);
  }
  delay(5000);
  xSample/=samples;
  ySample/=samples;
  zSample/=samples;
  digitalWrite(led, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Calibration Done !");
  delay(1000);
  lcd.clear();


  

}

void loop() {
  int value1 = analogRead(A0);
  int value2 = analogRead(A1);
  int value3 = analogRead(A2);

  int xValue = xSample - value1;
  int yValue = ySample - value2;
  int zValue = zSample - value3;

  int x = constrain(xValue, -20, 20); 
  int y = constrain(yValue, -20, 20); 
  int z = constrain(zValue, -20, 20); 
   if(state == 0 )
   {
   lcd.print("X       Y      Z");
   lcd.setCursor(0,1);
   lcd.print(x);
   lcd.setCursor(7,1);
   lcd.print(y);
   lcd.setCursor(14,1);
   lcd.print(z);
   delay(100);
   }
 // conditions for EarthQuake
 if(xValue < minVal || xValue > maxVal || yValue < minVal || yValue > maxVal || zValue < minVal || zValue > maxVal )
 {
  if(buz == 0)
  start = millis();   // timer start
  buz = 1;   
 }
 else if( buz == 1 )
 {
  lcd.setCursor(0,0);
  lcd.print("EarthQuake Alert ");
  if(millis() >= start + buzTime )
  buz = 0;
  if( button == HIGH)
  state = 0;
 }

 digitalWrite(buzzer,buz);
 digitalWrite(led, buz);

}

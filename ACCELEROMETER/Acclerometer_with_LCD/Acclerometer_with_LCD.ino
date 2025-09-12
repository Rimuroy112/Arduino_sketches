#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);
int Xread;
int Xrest;
int Yread;
int Yrest;
int Zread;
int Zrest;

double Gx;
double Gy;
double Gz;

int xPin = A0;
int yPin = A1;
int zPin = A2;


void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(2,0);
  lcd.print("Accelerometer!");
  delay(3000);
  digitalWrite(13, HIGH);
  delay(1000);
  Xrest = analogRead(xPin);
  Yrest = analogRead(yPin);
  Zrest = analogRead(zPin);
  digitalWrite(13, LOW);
  
  lcd.clear();

}

void loop() {
  Xread = analogRead(xPin)-Xrest;
  Yread = analogRead(yPin)-Yrest;
  Zread = analogRead(zPin)-Zrest;

  Gx = Xread/67.584;
  Gy = Yread/67.584;
  Gz = Zread/67.584;

  lcd.setCursor(0,0);
  lcd.print("Gx:");
  lcd.print(Gx);
  lcd.setCursor(9,0);
  lcd.print("Gy:");
  lcd.print(Gy);
  lcd.setCursor(0,1);
  lcd.print("Gz:");
  lcd.print(Gz);
  delay(1000);
  lcd.clear();

}

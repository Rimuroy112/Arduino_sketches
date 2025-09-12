#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

#define ADC_ref 5  // reference voltage
#define zero_x 1.799
#define zero_y 1.799
#define zero_z 1.799
#define trigPin 8
#define echoPin 9
#define selectSwitch 1
#define sensitivity_x 0.4
#define sensitivity_y 0.4
#define sensitivity_z 0.4
unsigned int value_x;
unsigned int value_y;
unsigned int value_z;
int distance,duration;
float x,y,z;
float angle;


void setup() {
  lcd.begin(16,2);
  analogReference(ADC_ref);
  pinMode(selectSwitch, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.setCursor(0,0);
  lcd.print("Degree &Distance");
  lcd.setCursor(0,1);
  lcd.print("Measurement !");
  delay(3000);
  lcd.clear();
  
}

void loop() {
  value_x = analogRead(A0);
  value_y = analogRead(A1);
  value_z = analogRead(A2);
  x = ((value_x/1024.0)*ADC_ref-zero_x)/sensitivity_x;
  y = ((value_y/1024.0)*ADC_ref-zero_y)/sensitivity_y;
  z = ((value_z/1024.0)*ADC_ref-zero_z)/sensitivity_z;
  angle = atan2(-y,-z)*57.2957795+180;
  if(digitalRead(selectSwitch)==HIGH)
  {
    lcd.setCursor(0,0);
    lcd.print("Tilt: ");
    lcd.print(angle);
    lcd.print(" deg");
    
  digitalWrite(trigPin,LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  distance=duration*.034/2;

  if(distance >= 400 || distance <= 0)
  {
    lcd.setCursor(0,1);
    lcd.print("Out of Range");
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm ");
  }
   delay(1000);
   lcd.clear();
   
 }
 else
 {
  lcd.setCursor(0,0);
  lcd.print("X=");
  lcd.print(x);
  lcd.print(" Y=");
  lcd.print(y);
  lcd.setCursor(0,1);
  lcd.print(" Z= ");
  lcd.print(z);
  delay(1000);
  
 }

}

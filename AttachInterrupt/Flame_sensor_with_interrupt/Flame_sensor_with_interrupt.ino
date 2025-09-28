#include <LowPower.h>

void turnOn();
void turnOff();

void setup() {
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  attachInterrupt(0,turnOn, FALLING);
  attachInterrupt(1, turnOff,RISING);

}

void loop() {
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}



void turnOn()
{
  digitalWrite(6, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(7, HIGH);
}
void turnOff()
{
  digitalWrite(6, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(7, LOW);
}

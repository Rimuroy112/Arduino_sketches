#include <RH_ASK.h>
#include <SPI.h>


const int buzzer = 7;
RH_ASK rf_driver;

void setup() {
  Serial.begin(9600);   // For debugging purpose
  pinMode(buzzer, OUTPUT);
  if(!rf_driver.init())
    Serial.println("Init failed ");

}

void loop() {
 uint8_t buf[1];
 uint8_t buflen = sizeof(buf);

 if(rf_driver.recv(buf, &buflen))
 {
  Serial.println("There is a person outside the door ");
  digitalWrite(buzzer, HIGH);
  delay(10000);
 
  Serial.println("Stop");
 }
 else
  digitalWrite(buzzer, LOW);

}

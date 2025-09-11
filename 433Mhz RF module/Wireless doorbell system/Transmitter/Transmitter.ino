#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;


void setup() {
  Serial.begin(9600);   // For debugging purpose
  pinMode(5, INPUT);
  if(!rf_driver.init())
    Serial.print("Init failed");

}

void loop() {
  if(digitalRead(5) == HIGH)
  {
    const char *msg = 'a';
    rf_driver.send((uint8_t*)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(200);
  }

}

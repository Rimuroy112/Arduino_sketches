#include <RH_ASK.h>        // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h>          // Include dependant SPI library

RH_ASK rf_driver;        // Create Amplitude Shift keying object

void setup() {
  rf_driver.init();   // Initialize Ask object
  Serial.begin(9600);

}

void loop() {
  uint8_t buf[11];
  uint8_t buflen = sizeof(buf);

  if(rf_driver.recv(buf, &buflen))    // check if received packet is correct size
  {
    // message received with valid checksum
    Serial.print("Message Received! ");
    Serial.println((char*)buf);
  }

}

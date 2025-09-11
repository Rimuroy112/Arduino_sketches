#include <SPI.h>     // Include dependant SPI library
#include <RH_ASK.h>  // Include RadioHead Amplitude Shift Keying Library

RH_ASK rf_driver;     // Create Amplitude Shift Keying object

void setup() {
  // Initialize ASK object
  rf_driver.init();

}

void loop() {

  const char *msg = "Hello World";
  rf_driver.send((uint8_t *)msg, strlen(msg));
  rf_driver.waitPacketSent();
  delay(1000);
  

}

#include <RH_ASK.h>
#include <SPI.h>

String str_humid;
String str_temp;
String str_out;
RH_ASK rf_driver;

void setup() {
  Serial.print(9600);
  rf_driver.init();


}

void loop() {
  // set buffer to size of expected message
  uint8_t buf[11];
  uint8_t buflen = sizeof(buf);
  // check if received packet is correct size
  if(rf_driver.recv(buf, &buflen))
  {
    // message received with valid checksum
    // Get values from string
    // convert received data into string
    str_out = String((char*)buf);
    // Split string into two values
    for(int i = 0; i < str_out.length(); i++)
    {
      if(str_out.substring(i, i+1) == ",")
      {
        str_humid = str_out.substring(0,i);
        str_temp = str_out.substring(i+1);
        break;
      }
    }
    // print values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(str_humid);
    Serial.print(" - Temperature: ");
    Serial.println(str_temp);
    
  }

}

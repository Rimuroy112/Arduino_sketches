#include <RH_ASK.h>
#include <SPI.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 7
#define DHTTYPE DHT22

float hum;
float temp;
String str_humid;
String str_temp;
String str_out;

RH_ASK rf_driver;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);  // For debugging purpose
  dht.begin();
  if (!rf_driver.init())
    Serial.println("rf_driver.init failed");

}

void loop() {
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  if(isnan(hum) || isnan(temp))
  {
    Serial.println("Failed to read the sensor ");
  }
  // convert humidity to string
  str_humid = String(hum);
  // convert temperature to string
  str_temp = String(temp);
  // Combine humidity and temperature
  str_out = str_humid + "," + str_temp;
  // compose output character
  static char *msg = str_out.c_str();

  rf_driver.send((uint8_t*)msg, strlen(msg));
  rf_driver.waitPacketSent();

}

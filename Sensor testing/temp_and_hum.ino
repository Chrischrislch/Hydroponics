#include "DHT.h"
#define DHTPIN 4        // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
void setup() {
 Serial.begin(9600);
 dht.begin();
}
void loop() {
 // Wait a few seconds between measurements.
 delay(2000);
// Reading temperature or humidity takes about 250 milliseconds!
 float humidity = dht.readHumidity();
 float temperature = dht.readTemperature();
 Serial.print(F("Humidity: "));
 Serial.print(humidity);
 Serial.print(F("%  Temperature: "));
 Serial.print(temperature);
 Serial.print(F("°C \n"));
}

#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


float maxTemperature = -100.0;
float minTemperature = 100.0;
float hum = dht.readHumidity();

void setup() {
  Serial.begin(9600);
  dht.begin();

void loop() {
  delay(2000);

  float t = dht.readTemperature();

  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float tF = (t * 9.0 / 5.0) + 32.0;

  if (t > maxTemperature) {
    maxTemperature = t;
  }
  if (t < minTemperature) {
    minTemperature = t;
  }

  Serial.print("Current Temperature: ");
  Serial.print(tF);
  Serial.println(" °F");

  Serial.print("Max Temperature: ");
  Serial.print((maxTemperature * 9.0 / 5.0) + 32.0);
  Serial.println(" °F");
  
  Serial.print("Min Temperature: ");
  Serial.print((minTemperature * 9.0 / 5.0) + 32.0);
  Serial.println(" °F");
}
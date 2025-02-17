#include <DHT.h> 

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);

  float tempc = dht.readTemperature();

  if (isnan(tempc)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("TemperatureC:");
  Serial.print(tempc);
  Serial.println();
}
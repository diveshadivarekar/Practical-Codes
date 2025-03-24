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
  float tempf = (tempc * 9.0 / 5.0) + 32.0;
  float hum = dht.readHumidity();

  if (isnan(tempc)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }


  Serial.print("TemperatureC:");
  Serial.print(tempc);
  Serial.print("\t");

  Serial.print("TemperatureF:");
  Serial.print(tempf);
  Serial.print("\t");

  Serial.print("Humidity:");
  Serial.print(hum);
  Serial.println();

}

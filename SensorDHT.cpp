#include "SensorDHT.h"

SensorDHT::SensorDHT(int pin, int type) : dhtPin(pin), dht(pin, type) {}

void SensorDHT::begin() {
  dht.begin();
}

float SensorDHT::getTemperature() {
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Error reading temperature!");
  }
  return temperature;
}

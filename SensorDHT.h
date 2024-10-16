#ifndef SENSORDHT_H
#define SENSORDHT_H

#include "DHT.h"

class SensorDHT {
  private:
    int dhtPin;
    DHT dht;

  public:
    SensorDHT(int pin, int type);
    void begin();
    float getTemperature();
};

#endif //SENSORDHT_H

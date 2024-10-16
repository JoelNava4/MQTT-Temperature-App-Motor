#ifndef MOTORACTUATOR_H
#define MOTORACTUATOR_H

#include <Arduino.h>

class MotorActuator {
  private:
    int motorPin;

  public:
    MotorActuator(int pin);
    void begin();
    void turnOn();
    void turnOff();
};

#endif //MOTORACTUATOR_H

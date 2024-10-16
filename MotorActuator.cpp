#include "MotorActuator.h"

MotorActuator::MotorActuator(int pin) : motorPin(pin) {}

void MotorActuator::begin() {
  pinMode(motorPin, OUTPUT);
}

void MotorActuator::turnOn() {
  digitalWrite(motorPin, HIGH);
  Serial.println("Motor turned ON");
}

void MotorActuator::turnOff() {
  digitalWrite(motorPin, LOW);
  Serial.println("Motor turned OFF");
}

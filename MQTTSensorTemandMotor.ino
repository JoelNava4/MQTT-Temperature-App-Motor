#include <Arduino.h>
#include "WiFiMQTT.h"
#include "SensorDHT.h"
#include "MotorActuator.h"

const char* SSID = "jota";
const char* PASSWORD = "joelnava4";
const char* MQTT_SERVER = "broker.hivemq.com";
const int MQTT_PORT = 1883;
const char* MQTT_TOPIC = "Otto/babys";
const int MOTOR_PIN = 5;

MotorActuator motor(MOTOR_PIN);           
WiFiMQTT wifiMqtt(SSID, PASSWORD, MQTT_SERVER, MQTT_PORT, MQTT_TOPIC, &motor);
SensorDHT sensorDHT(4, DHT22); 

void setup() {
  Serial.begin(115200);

  wifiMqtt.setupWiFi();     
  wifiMqtt.setupMQTT();     
  sensorDHT.begin();        
  motor.begin();            
}

void loop() {
  wifiMqtt.loop();  

  float temperature = sensorDHT.getTemperature();

  if (!isnan(temperature)) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");

    wifiMqtt.publishTemperature(temperature);
  } else {
    Serial.println("Error reading DHT sensor");
  }

  delay(2000); 
}

#ifndef WIFIMQTT_H
#define WIFIMQTT_H

#include <WiFi.h>
#include <PubSubClient.h>
#include "MotorActuator.h"

class WiFiMQTT {
  private:
    const char* SSID;
    const char* PASSWORD;
    const char* MQTT_SERVER;
    const int MQTT_PORT;
    const char* MQTT_TOPIC;
    WiFiClient espClient;
    PubSubClient client;
    MotorActuator* motor;  
    float previousTemperature = -999.0;
    
  public:
    WiFiMQTT(const char* SSID, const char* PASSWORD, const char* MQTT_SERVER,const int MQTT_PORT, const char* MQTT_TOPIC, MotorActuator* motor);
    void setupWiFi();
    void setupMQTT();
    void reconnect();
    void publishTemperature(float temperature);
    void callback(char* topic, byte* message, unsigned int length);
    void loop();
};

#endif //WIFIMQTT_H

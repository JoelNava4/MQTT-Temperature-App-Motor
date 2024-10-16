#include "WiFiMQTT.h"
#include <functional> 

WiFiMQTT::WiFiMQTT(const char* SSID, const char* PASSWORD, const char* MQTT_SERVER,const int MQTT_PORT, const char* MQTT_TOPIC, MotorActuator* motor)
  : SSID(SSID), PASSWORD(PASSWORD), MQTT_SERVER(MQTT_SERVER), MQTT_PORT(MQTT_PORT), MQTT_TOPIC(MQTT_TOPIC), client(espClient), motor(motor) {}

void WiFiMQTT::setupWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void WiFiMQTT::setupMQTT() {
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(std::bind(&WiFiMQTT::callback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void WiFiMQTT::reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("Ottito")) {
      Serial.println("connected");
      client.subscribe(MQTT_TOPIC); 
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void WiFiMQTT::publishTemperature(float temperature) {
  if (temperature != previousTemperature) {
    String tempMessage = String(temperature) + " °C";
    client.publish(MQTT_TOPIC, tempMessage.c_str());  
    previousTemperature = temperature;  
    Serial.println("Temperature change detected, sent to MQTT broker");
  }
}

void WiFiMQTT::callback(char* topic, byte* message, unsigned int length) {
  String receivedMessage = "";

  for (int i = 0; i < length; i++) {
    receivedMessage += (char)message[i];
  }

  receivedMessage.trim();
  Serial.print("Message received on topic [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(receivedMessage);
  if (receivedMessage.equalsIgnoreCase("ON")) {
    motor->turnOn();  
  } else if (receivedMessage.equalsIgnoreCase("OFF")) {
    motor->turnOff();  
  }
}

void WiFiMQTT::loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

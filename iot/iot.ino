#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

// [DHT22]
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float h;
float t;

// [LED]
#define BUILTIN_LED 2

// [MQTT]
const char* user = "onlyramdan";
const char* user_pass = "Sarimiisi8";
const char* ssid = "IJDYH";
const char* password = "dindayusufhasan05";
const char* mqtt_server = "103.189.235.124";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

//[Fungsi-fungsi] 

// -MQTT
void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

// -DHT22
void dht22();

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  dht22();
  
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "{\n  \"suhu\": %.2f,\n  \"kelembaban\": %.2f\n}",t,h);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }
}

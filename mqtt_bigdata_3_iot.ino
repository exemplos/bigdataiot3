#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid     = "iot";
const char* password = "12348765";

WiFiClient CLIENT;
PubSubClient MQTT(CLIENT);

unsigned long lastTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  MQTT.setServer("iot.franciscocalaca.com", 1883);
  MQTT.setCallback(lerMensagem);
}

void lerMensagem(char* topic, byte* payload, unsigned int length){
  DynamicJsonBuffer jsonBuffer;
  String json = (char*)payload;
  Serial.println(json);
  JsonObject& rootRead = jsonBuffer.parseObject(json);
  long number = rootRead["number"];
  if(number == 1){
    digitalWrite(2, HIGH);
    Serial.println("...ligar");
  }else{
    digitalWrite(2, LOW);
    Serial.println("...desligar");
  }  
}

void reconnect() {
  while (!MQTT.connected()) {
    if (MQTT.connect("SENSOR-01")) {
      MQTT.subscribe("hello/world");
    } else {
      Serial.print(".");
      delay(3000);
    }
  }
}

void loop() {
  reconnect();
  MQTT.loop(); 
  unsigned long time = millis() - lastTime;
  if(time > 2000){
    MQTT.publish("python/test", "do iot...");
    lastTime = millis();  
  }
  

}

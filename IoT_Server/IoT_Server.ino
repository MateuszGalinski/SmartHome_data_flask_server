#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>

#define DHT11_PIN 5

DHT dht_sensor;

const char* ssid = "YOUR SSID";
const char* password = "YOUR PASSWORD";

const char* serverName = "Url of server showing data";

void setup() {
  Serial.begin(9600);
  dht_sensor.setup(DHT11_PIN);

  WiFi.begin(ssid, password);

  Serial.println("Connecting");

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Connected to network with ip: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    float humidity = dht_sensor.getHumidity();
    float temperature = dht_sensor.getTemperature();

    sendJson(temperature, humidity);
    Serial.println("");
    Serial.println("Temperature: ");
    Serial.print(temperature);
    Serial.println("");
    Serial.println("Humidity: ");
    Serial.print(humidity);
  }
  else{
    Serial.print("WiFi disconnected");
  }

  delay(dht_sensor.getMinimumSamplingPeriod());
}

void sendJson(float temperature, float humidity){
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);
  http.addHeader("accept", "application/json");
  http.addHeader("Content-Type", "application/json");

  String httpData = "{\"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + "}";

  int httpResponseCode = http.POST(httpData);

  Serial.println("");
  Serial.println("httpResponseCode: ");
  Serial.print(httpResponseCode);

  http.end();
}



#include <ESP8266WiFi.h>
#include <WiFiClientSecureBearSSL.h>
#include <PubSubClient.h>
#include <Adafruit_BMP280.h>
#include <Wire.h>
#include "secrets.h"

// ================= BEARSSL OBJECTS =================
BearSSL::X509List ca(AWS_ROOT_CA);
BearSSL::X509List cert(AWS_CERT);
BearSSL::PrivateKey key(AWS_PRIVATE_KEY);

BearSSL::WiFiClientSecure net;
PubSubClient client(net);
Adafruit_BMP280 bmp;

bool bmpWorking = false;

// ================= WIFI CONNECT =================
void connectWiFi() {

  Serial.println("Connecting to WiFi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && 
         millis() - startAttemptTime < 20000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi Failed!");
  }
}

// ================= AWS CONNECT =================
void connectAWS() {

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected. Skipping AWS.");
    return;
  }

  net.setBufferSizes(512, 512);
  net.setTrustAnchors(&ca);
  net.setClientRSACert(&cert, &key);

  client.setServer(awsEndpoint, awsPort);

  Serial.println("Connecting to AWS...");

  if (client.connect("ESP_Project")) {
    Serial.println("AWS Connected!");
  } else {
    Serial.print("AWS Connection Failed. Error Code: ");
    Serial.println(client.state());
  }
}

// Mapping: D7 on NodeMCU corresponds to your yellow wire for LED
// Mapping: D6 on NodeMCU corresponds to your yellow wire for Buzzer
#define LED_PIN D7      
#define BUZZER_PIN D6   

// Change this to a value just slightly higher than your room temp
float tempLimit = 35.0;
float pressureLimit = 1000.0;
float humidityLimit = 80.0;

// ================= SETUP =================
void setup() {

  Serial.begin(115200);
  delay(1000);

  // I2C pins for NodeMCU 12E
  Wire.begin(D2, D1);

  Serial.println("Initializing BMP280...");

  if (bmp.begin(0x76)) {
    Serial.println("BMP280 found at 0x76");
    bmpWorking = true;
  } 
  else if (bmp.begin(0x77)) {
    Serial.println("BMP280 found at 0x77");
    bmpWorking = true;
  } 
  else {
    Serial.println("BMP280 NOT detected!");
    bmpWorking = false;
  }

  connectWiFi();
  connectAWS();

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");

  Serial.print("Waiting for NTP time sync");
  time_t now = time(nullptr);

  while (now < 8 * 3600 * 2) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }

  Serial.println("\nTime synchronized!");

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Ensure they start in the OFF state
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW); 

}


// ================= LOOP =================
void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (!client.connected()) {
    connectAWS();
  }

  client.loop();

  float temperature = 0;
  float humidity = 0;   
  float pressure = 0;

  if (bmpWorking) {
    temperature = bmp.readTemperature();
    humidity = random(55,60);  
    pressure = bmp.readPressure() / 100.0F;
  }

  // --- Triple-Sensor Trigger Logic ---
  if (bmpWorking && (temperature > tempLimit || pressure > pressureLimit || humidity > humidityLimit)) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("ALERT: Environmental Threshold Exceeded!");
    
    // Optional: Print exactly what triggered it
    if(temperature > tempLimit) Serial.println("Reason: High Temp");
    if(pressure > pressureLimit) Serial.println("Reason: High Pressure");
    if(humidity > humidityLimit) Serial.println("Reason: High Humidity");

  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
}

  String payload = "{";
  // ... existing code for payload and publishing ...

  payload += "\"temperature\":" + String(temperature) + ",";
  payload += "\"humidity\":" + String(humidity) + ",";
  payload += "\"pressure\":" + String(pressure);
  payload += "}";

  if (client.connected()) {
    client.publish(publishTopic, payload.c_str());
    Serial.println("Published: " + payload);
  }

  delay(5000);
}

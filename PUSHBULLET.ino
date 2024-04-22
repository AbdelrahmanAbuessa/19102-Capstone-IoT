// send messages using pushbullet and pushingbox
// TX -> TX
// RX -> RX
// EN -> 3.3v
// 3.3v -> 3.3v
// GND -> GND

#include <ESP8266WiFi.h>

// PushingBox scenario DeviceId code and API
String deviceId = "vFAFB6E22D0CEEAB";
const char* logServer = "api.pushingbox.com";

const char* ssid = "Tbh yall should watch bluey rn";
const char* password = "handitbeeler";

void setup() {
  Serial.begin(57600);
  // Sending a notification to your mobile phone
  // function takes the message as a parameter
  sendNotification("19202 ON TOP");
}

void sendNotification(String message){

  Serial.println("- connecting to Home Router SID: " + String(ssid));
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("- succesfully connected");
  Serial.println("- starting client");
  
  WiFiClient client;

  Serial.println("- connecting to pushing server: " + String(logServer));
  if (client.connect(logServer, 80)) {
    Serial.println("- succesfully connected");
    
    String postStr = "devid=";
    postStr += String(deviceId);
    postStr += "&message_parameter=";
    postStr += String(message);
    postStr += "\r\n\r\n";
    
    Serial.println("- sending data...");
    
    client.print("POST /pushingbox HTTP/1.1\n");
    client.print("Host: api.pushingbox.com\n");
    client.print("Connection: close\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }
  client.stop();
  Serial.println("- stopping the client");
}

void loop() {
  }

//send text to line
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <ArtronShop_LineNotify.h>

#define WIFI_SSID "WIFI_NAME"
#define WIFI_PASSWORD "WIFI_PASS" 

#define LINE_TOKEN "aZ6DvBdp2qdQP9DRbHz59WoSQndYeZH9QjFk3IfGbAk"

WiFiMulti wifiMulti;

void setup(){
  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
}

void loop(){
  Serial.print("Waiting for WiFi to connect...");
  while ((wifiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
  }
  Serial.println(" connected");

  LINE.begin(LINE_TOKEN);

  if (LINE.send("อย่าลืมทำโจทย์")) {
    Serial.println("Send notify successful");
  } else {
    Serial.printf("Send notify fail. check your token (code: %d)\n", LINE.status_code);
  }
}




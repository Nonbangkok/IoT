//send value to control flash usb from blynk
#define BLYNK_TEMPLATE_ID "TMPL6mPkdRU_o"
#define BLYNK_TEMPLATE_NAME "Nonbangkok"
#define BLYNK_AUTH_TOKEN "mNFSXMSQ5UcENLtNiCarlJJlNsJ-jFqm"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "WIFI_NAME";
char pass[] = "WIFI_PASS";

BLYNK_WRITE(V0){
    int pinValue = param.asInt();
    Serial.print("V1 Slider value is: ");
    Serial.println(pinValue);
    digitalWrite(25,!pinValue);
}

void setup(){
    Serial.begin(115200);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    pinMode(25,OUTPUT);
}

void loop(){
    Blynk.run();
}






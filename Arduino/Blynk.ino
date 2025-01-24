//send timer and temperature to blynk
#define BLYNK_TEMPLATE_ID "TMPL6vZwEIu8p"
#define BLYNK_TEMPLATE_NAME "LAP6"
#define BLYNK_AUTH_TOKEN "LdW0xeA79S_CwsBqaDxAoMxwIEidTI5Z"
#define LM73_ADDR 0x4D
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>

float readTemperature(){
    Wire1.beginTransmission(LM73_ADDR);
    Wire1.write(0x00);
    Wire1.endTransmission();

    uint8_t count = Wire1.requestFrom(LM73_ADDR, 2);
    float temp = 0.0;
    if (count == 2){
        byte buff[2];
        buff[0] = Wire1.read();
        buff[1] = Wire1.read();
        temp += (int)(buff[0] << 1);
        if (buff[1] & 0b10000000) temp += 1.0;
        if (buff[1] & 0b01000000) temp += 0.5;
        if (buff[1] & 0b00100000) temp += 0.25;
        if (buff[0] & 0b10000000) temp *= -1.0;
    }
    return temp;
}

char ssid[] = "WIFI_NAME";
char pass[] = "WIFI_PASS";

BlynkTimer timer;

void myTimerEvent(){
    Blynk.virtualWrite(V0, readTemperature());
    Blynk.virtualWrite(V1, millis() / 1000);
}

void setup(){
    Serial.begin(115200);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    timer.setInterval(1000L, myTimerEvent);
    Wire1.begin(4, 5);
}

void loop(){
    Blynk.run();
    timer.run();
}
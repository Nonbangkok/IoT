//send value 2 way, line notify + Blynk
#define BLYNK_TEMPLATE_ID "TMPL6tVUt94fN"
#define BLYNK_TEMPLATE_NAME "Project IOT"
#define BLYNK_AUTH_TOKEN "VmwyNzt1P4jkLAUsMNZgGhnV5iDQg0US"
#define LINE_TOKEN "jlnNvcutodVFYM7kdOqp0xS7hBgutTaDWpcwjyKh7n0"

#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ArtronShop_LineNotify.h>

char ssid[] = "WIFI_NAME";
char pass[] = "WIFI_PASS";
int reset=0,value_alert=0,timee=0,previous_time=0,chk=0;

BlynkTimer timer;
WiFiMulti wifiMulti;

void myTimerEvent(){
  timee=(millis()/1000);
  if(reset&&chk){
    previous_time=timee;
    timee=0;
    chk=0;
  }
  chk=!reset;
  Blynk.virtualWrite(V0,timee-previous_time);
  if(timee-previous_time>=value_alert){
    //line notify
    while(true){
      if(wifiMulti.run()==WL_CONNECTED){
        LINE.begin(LINE_TOKEN);
        LINE.send("เวฟเสร็จแล้ว");
        break;
      }
    }
  }
}

BLYNK_WRITE(V1){
  reset = param.asInt();
}

BLYNK_WRITE(V2){
  value_alert = param.asInt();
}

void setup(){
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(ssid,pass);
}

void loop(){
  Blynk.run();
  timer.run();
}

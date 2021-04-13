#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

#define lightPin 13

boolean connectWifi();
void firstLightChanged(uint8_t brightness);

const char* ssid = "WIFI_NAME";
const char* password = "WIFI_PASSWORD";

String Device1 = "Room Light";
boolean wifiConnected = false;

Espalexa espalexa;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(lightPin, OUTPUT);

  wifiConnected = connectWifi();
  
  if(wifiConnected){
    espalexa.addDevice(Device1, firstLightChanged);

    espalexa.begin();
  }
  else{
    while(1){
      Serial.println("Cannot connect to Wifi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  espalexa.loop();
  delay(1);
}

void firstLightChanged(uint8_t brightness){
  if(brightness == 255){
    digitalWrite(lightPin, HIGH);
    Serial.println("lightPin ON");
  }
  else{
    digitalWrite(lightPin, LOW);
    Serial.println("lightPin OFF");
  }
}

boolean connectWifi(){
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to Wifi");

  Serial.print("Connecting....");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    if(i > 20){
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if(state){
    Serial.print("Connected: ");
    Serial.println(ssid);
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }
  else{
    Serial.println("Connection Failed.");
  }
  return state;
}

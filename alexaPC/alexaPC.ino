#include <Servo.h>
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

#define servoPin 5 //D1
Servo servo;

boolean connectWifi();
void turnPC(uint8_t brightness);

const char* ssid = "WIFI_NAME";
const char* password = "WIFI_PASSWORD";

int angle = 0;
String Device1 = "Computer";
boolean wifiConnected = false;

Espalexa espalexa;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  servo.attach(servoPin);
  
  wifiConnected = connectWifi();
  
  if(wifiConnected){
    espalexa.addDevice(Device1, turnPC);

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
  analogWrite(servoPin, 30000);
  delay(100);
}

void turnPC(uint8_t brightness){
  if(brightness == 255){
    for(angle = 90; angle > 60; angle--){                                  
      servo.write(angle);               
      delay(5);                   
    }
    for(angle = 60; angle < 90; angle++){                                
      servo.write(angle);           
      delay(5);       
    }
    Serial.println("servoPin ON");
  }
  else{
    for(angle = 90; angle > 60; angle--){                                  
      servo.write(angle);               
      delay(5);                   
    }
    for(angle = 60; angle < 90; angle++){                                
      servo.write(angle);           
      delay(5);       
    }
    Serial.println("servoPin OFF");
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

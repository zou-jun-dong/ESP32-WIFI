#include <WiFi.h>  //include the WI-FI library for ESP32
#include <Arduino.h>

//Set the SSID and password for the ESP32 Access Point
const char* AP_SSID="ESP32_AIoT_AP";
const char* AP_PASS="12345678";


void setup(){
  //Initialize serial communication at 115200 baud rate
  Serial.begin(115200);
  //Short delay to ensure the serial monitor is ready
  delay(1000);
  Serial.println("\n----------------------------------------");
  Serial.println("Congiguring Access Point...");
  //Set Wi-Fi mode to Access Point (AP),turningt the device into a hotpot
  WiFi.mode(WIFI_AP);
  //Start the Access Point
  bool result=WiFi.softAP(AP_SSID,AP_PASS);
  if (result)
  {
    /* code */
    Serial.println("AP Mode started successfully!");
      //Get the IP adress of the ESP32 AP (default is usually 192.168.4.1)
  IPAddress IP=WiFi.softAPIP();
  Serial.print("AP Ip Address");
  Serial.print(IP);
  }
   else
   {
    Serial.println("Failled to start AP Mode");

   }
   Serial.println("-------------------------------------------");
}

void loop(){
   //Your ESP32 is now continuously broadcasting its Wi-Fi signal
}
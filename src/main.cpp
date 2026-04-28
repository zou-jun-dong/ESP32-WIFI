#include <WiFi.h>  //include the WI-FI library for ESP32
#include "secrets.h"  //Include the header file with Wi-Fi credentials
#include <Arduino.h>
void setup(){
  //Initialize serial communication at 115200 baud rate
  Serial.begin(115200);
  //Short delay to ensure the serial monitor is ready
  delay(1000);
  Serial.println("\n----------------------------------------");
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  //Set Wi-Fi mode to Station (STA),acting as a client to connect to the router
  WiFi.mode(WIFI_STA);
  //Start connecting to Wi-Fi with credentials
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  //Cpntinuously check Wi-Fi connection status yntil successfully connnected
  //WiFi.status() returns the current connection status
  while (WiFi.status()!=WL_CONNECTED)
  {
    /* code */
    delay(500);  //Wait 500 milliseconds between checks
    Serial.print("."); //Print a dot to indicate it is tring to connect

  }
  //Exiting the loop means the connection was successful
  Serial.println("");
  Serial.println("Wi-Fi connectedd successfully!");
  //Get and print the local IP address assigned bt the router
  Serial.print("IP Adderess ");
  Serial.println(WiFi.localIP());
  Serial.println("----------------------------------------");
}

void loop(){
  //Today's task is to connect to the network on startup,so loop() can be empty for now
}
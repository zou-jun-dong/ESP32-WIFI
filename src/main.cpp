#include <WiFi.h>  //include the WI-FI library for ESP32
#include "secrets.h"  //Include the header file with Wi-Fi credentials
#include <Arduino.h>
#include <WebServer.h> //Include the Webserver library
//Create a WebServer instance on port 80
WebServer server(80);
//Function to handle requests to thr root path
void handleRoot(){
  //Define the HTML content to be displayed
  String html="<html><head><metacharset='UTF-8'></head><body>";
  html+="<h1>Hello AIoT!</h1>";
  html+="<p>Current Light Status: <b>ON</b></p>";
  html+="</body></html>";

  //Send HTTP 200 response with the HTML content
  server.send(200,"text/html",html);
}
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
  //Web Server Configuration
  
  //When a user accesses the root path,execute the handleRoot function
  server.on("/",handleRoot);

  //Start the server
  server.begin();
  Serial.println("HTTP Server started.");
}

void loop(){
  //Continuously handle incoming requests from clients(btowsers)
  server.handleClient();
}
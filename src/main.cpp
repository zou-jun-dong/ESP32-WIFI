#include "WiFi.h"  //include the WI-FI library for ESP32
void setup(){
  //Initialize serial communication at 115200 baud rate
  Serial.begin(115200);
  //Set WI-FI mode to Station(STA),acting as a client
  WiFi.mode(WIFI_STA);
  //Disconnect from any previous connections to ensure accurate scanning 
  WiFi.disconnect();
  //Short delay to wait for the Wi-Fi module to be ready
  delay(1000);
  Serial.println("Setup completed.Ready to scan...");
}

void loop(){
  Serial.println("----------------------------------------");
  Serial.println("Starting Wi-Fi scan...");
  //scanNetworkes() returns the number of networks found
  int n=WiFi.scanNetworks();
  Serial.println("Scan completed.");
  if (n==0)
  {
    /* code */
    Serial.println("No networks found.");
    
  }
  else
  {
    //Print the number of networks found
    Serial.print(n);
    Serial.println("networks found.");
    //Iterate and print details of each network
    for (int i = 0; i < n; i++)
    {
      /* code */
      Serial.print(i+1);//Print index
      Serial.print(":");
      Serial.print(WiFi.SSID(i));//Print network name
      Serial.print("(RSSI:");//Print signal strength
      Serial.print(WiFi.RSSI(i));
      Serial.print("dBm)");
      //Check if the network is encrypted,print "*" if it's not an open network
      Serial.println((WiFi.encryptionType(i)==WIFI_AUTH_OPEN?" [OPEN/公开]" : " *[ENCRYPTED/加密]"));
      delay(10);//Short delay to stabilize serial output
      
    }
    
  }
  //Print a newline and wait for 5 seconds before the next scan
  Serial.println("");
  delay(5); 

  
}
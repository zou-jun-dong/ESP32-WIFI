#include <Arduino.h>
#include <WiFi.h>
#include <secrets.h>
#include <WebServer.h>

const int ledPin=2;  //Define the LED pin

bool isBreathing=false;   //Whether breathing mode is active 
int brightness=0;   //Current brightness
int fadeAmount=5;   //Fade increment amount


WebServer server(80);

//Handle root requests and display the control panel
void handleRoot()
{
  String statusText= isBreathing ? "RUNNING":"STOPPED";
   String html = "<html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<style>body{text-align:center;font-family:sans-serif;} .btn{padding:20px;font-size:20px;margin:10px;cursor:pointer;}</style>";
  html += "</head><body>";
  html += "<h1>ESP32 联网呼吸灯</h1>";
  html += "<p>当前状态: <b>" + statusText + "</b></p>";
  html += "<button class='btn' onclick=\"location.href='/on'\">开启呼吸 (ON)</button>";
  html += "<button class='btn' onclick=\"location.href='/off'\">关闭灯光 (OFF)</button>";
  html += "</body></html>";
  server.send(200,"text/html",html);
}

void setup(){
  Serial.begin(115200);
  pinMode(ledPin,OUTPUT);  //Configure the LED pin as output
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  while (!WiFi.isConnected())
  {
    Serial.println(".");
    delay(500);
  }
   Serial.println("\nWi-Fi Connected. IP: " + WiFi.localIP().toString());
   server.on("/",handleRoot);  //Route configuration
   //Endpoint to start breathing
   server.on("/on",[]() {
    isBreathing =true;
    server.sendHeader("Location","/");
    server.send(303);
   });
   //Endpoint to turn off breathing
   server.on("/off",[](){
    isBreathing=false;
    analogWrite(ledPin,0);
    server.sendHeader("Location","/");
    server.send(303);
   });
   server.begin();
}

void loop(){
  server.handleClient();  //Handle web requests
  if (isBreathing)
  {
    //Use analogWrite for PWM bringtness control
    analogWrite(ledPin,brightness);
    //Change brightness for next iteration
    brightness=brightness+fadeAmount;
    //Reverse fading direction at boundaries
    if (brightness<=0||brightness>=255)
    {
      fadeAmount=-fadeAmount;
    }
    
  }
  delay(30); //Control breathing speed
  

}
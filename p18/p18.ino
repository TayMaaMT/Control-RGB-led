
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "file.h";

const char *ssid = "PRC4";
const char *password = "ecom5333";
bool GPIO3State = 0; 

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 11);
DNSServer dnsServer;
ESP8266WebServer webServer(80);


void handleRoot() {
// Serial.println("handle root..");
String red = webServer.arg(0); // read RGB arguments
String green = webServer.arg(1);
String blue = webServer.arg(2);

analogWrite(0, red.toInt());
analogWrite(2, green.toInt());
analogWrite(3, blue.toInt());

// Serial.println(red.toInt()); // for TESTING
// Serial.println(green.toInt()); // for TESTING
// Serial.println(blue.toInt()); // for TESTING
webServer.send(200, "text/html", webpage);
}
void handleToggle()
{
  GPIO3State = ! GPIO3State;
  digitalWrite(0,LOW);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  if (GPIO3State == 0) 
      webpage.replace(" button2\">OFF" , "button\">ON");
  else 
     webpage.replace("button\">ON" , " button2\">OFF");
  webServer.send(200, "text/html", webpage);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

pinMode(0, OUTPUT);
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);

analogWrite(0, 1023);
analogWrite(2, 1023);
analogWrite(3, 1023);

delay(1000);
// Serial.begin(9600);
// Serial.println();

WiFi.mode(WIFI_AP);
WiFi.begin(ssid,password);
WiFi.config(apIP, apIP, IPAddress(255, 255, 255, 0));


// if DNSServer is started with "*" for domain name, it will reply with provided IP to all DNS request
dnsServer.start(DNS_PORT, "rgb", apIP);

webServer.on("/", handleRoot);
webServer.on("/", handleToggle);

webServer.begin();

testRGB();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {

dnsServer.processNextRequest();
webServer.handleClient();

}
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void testRGB() { // fade in and out of Red, Green, Blue

analogWrite(0, 1023); // R off
analogWrite(2, 1023); // G off
analogWrite(3, 1023); // B off

fade(0); // R
fade(2); // G
fade(3); // B
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void fade(int pin) {

for (int u = 0; u < 1024; u++) {
analogWrite(pin, 1023 - u);
delay(1);
}
for (int u = 0; u < 1024; u++) {
analogWrite(pin, u);
delay(1);
}
}

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WifiService.h>
#include<UDPService.h>

////////// Wifi Konfiguration /////////////
const char *SSID = "TP-LINK_D8BA";
const char *PASS = "35581338";
////////// UDP Konfigration ///////////////
const int LOCAL_LISTEN_PORT = 8080; //UDP port
const int MAX_BUFFER_LENGTH = 20;

IPAddress multicastIP(224,0,0,0); //IP des Multicast
const int MULTICAST_PORT = 8081; //IP des Multicast
byte SERVER_IP[4]; //IP des Servers
int SERVER_PORT; //PORT des Servers

/////////// WIFI Und UDP erstellen/////////
WifiService wifi(SSID, PASS);
UDPService Udp;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  wifi.connectToWifi();
  Udp.setupListenPort(LOCAL_LISTEN_PORT);
  // Udp.setupMulticastServer(multicastIP,MULTICAST_PORT);
  // Udp.sendToServer("Hi");
}

void loop()
{
  // put your main code here, to run repeatedly:
  char* received = Udp.getMessageFromServer(MAX_BUFFER_LENGTH);
}
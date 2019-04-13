#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WifiService.h>
#include <UDPService.h>

////////// Wifi Konfiguration /////////////
const char *SSID = "TP-LINK_D8BA";
const char *PASS = "35581338";
////////// UDP Konfigration ///////////////
const int LOCAL_LISTEN_PORT = 8080; //UDP port
const int MAX_BUFFER_LENGTH = 25;   //Max. Länge des Pakets

IPAddress multicastIP(224, 0, 0, 0); //IP des Multicast
const int MULTICAST_PORT = 8081;     //IP des Multicast

IPAddress ServerIP(192, 168, 0, 104); //IP des Server Rechners
const int Server_PORT = 8080;// Server Port

/////////// WIFI Und UDP erstellen/////////
WifiService wifi(SSID, PASS);
UDPService Udp;

// Testprogramm zum Hören vom server
void setup()
{
  Serial.begin(9600);
  wifi.connectToWifi();
  Udp.setupListenPort(LOCAL_LISTEN_PORT);
  Udp.setupMulticastServer(multicastIP, MULTICAST_PORT);
  Udp.setupServer(ServerIP, Server_PORT);
  Udp.sendToServer("Hi at setup ");
}

void loop()
{
  delay(2000);
  Udp.sendToServer("Hi loop");
}
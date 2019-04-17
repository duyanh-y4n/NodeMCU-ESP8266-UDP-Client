#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WifiService.h>
#include <MDClient.h>

////////// Wifi Konfiguration /////////////
const char *SSID = "TP-LINK_D8BA";
const char *PASS = "35581338";
// const char *SSID = "Y4NAP";
// const char *PASS = "12312345";
////////// UDP Konfigration ///////////////
const int LOCAL_LISTEN_PORT = 8080; //UDP port
const int MAX_BUFFER_LENGTH = 25;   //Max. Länge des Pakets

IPAddress multicastIP(224, 0, 0, 0); //IP des Multicast
const int MULTICAST_PORT = 8081;     //IP des Multicast

IPAddress *ServerIP; //IP des Server Rechners
const int Server_PORT = 8080;         // Server Port

/////////// WIFI Und UDP erstellen/////////
WifiService wifi(SSID, PASS);
MDClient Udp;

// Testprogramm zum Hören vom server
void setup()
{
  Serial.begin(9600);
  wifi.connectToWifi();
  Udp.setupListenPort(LOCAL_LISTEN_PORT);
  Udp.connectToLeitSystemServer(multicastIP, MULTICAST_PORT);
  Udp.sendToServer("Hi From Node ");
}

void loop()
{
  char* received = Udp.getMessageFromServer(20);
  if (received!=NULL)
  {
    /* code */
    Serial.println(received);
  }
  delay(1000);
  
}
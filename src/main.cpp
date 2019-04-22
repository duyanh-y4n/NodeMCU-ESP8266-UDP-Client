#include <Arduino.h>

// needed lib
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "WifiService.h"
#include "MDClient.h"

////////// Wifi Konfiguration /////////////
const char *SSID = "TP-LINK_D8BA";
const char *PASS = "35581338";
// const char *SSID = "Y4NAP";
// const char *PASS = "12312345";

////////// LeitSystemClient Konfigration ///////////////
const int LOCAL_LISTEN_PORT = 8080; //LeitSystemClient port
const int MAX_BUFFER_LENGTH = 20;   //Max. Länge des Pakets

IPAddress multicastIP(224, 0, 0, 0); //IP des Multicast
const int MULTICAST_PORT = 8081;     //IP des Multicast

IPAddress ServerIP(192,168,0,104); //IP des Server Rechners
const int Server_PORT = 8080;         // Server Port

///////////Client Info/////////////////////
char *clientName = "MDCar1";
int id;

/////////// WIFI Und LeitSystemClient erstellen/////////
WifiService wifi(SSID, PASS);
MDClient LeitSystemClient;

// Testprogramm zum Hören vom server
void setup()
{
  Serial.begin(9600);
  wifi.connectToWifi();
  LeitSystemClient.setupListenPort(LOCAL_LISTEN_PORT);
  LeitSystemClient.connectToLeitSystemServer(multicastIP, MULTICAST_PORT);
  LeitSystemClient.registerToSystem(clientName);
  id = LeitSystemClient.getId();
}

void loop()
{
  // LeitSystemClient.getMessageFromMulticastServer(20);
  char* received = LeitSystemClient.getMessageFromServer(MAX_BUFFER_LENGTH);
  if (received!=NULL && received[0]==0x11)
  {
    Serial.println(received);
    for (int i = 0; i < MAX_BUFFER_LENGTH; i++)
    {
      Serial.print(" ");
    }
      Serial.println();
  }
}
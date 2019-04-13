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
const int MAX_BUFFER_LENGTH = 25;

IPAddress multicastIP(224, 0, 0, 0); //IP des Multicast
const int MULTICAST_PORT = 8081;     //IP des Multicast
byte SERVER_IP[4];                   //IP des Servers
int SERVER_PORT;                     //PORT des Servers

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
}

void loop()
{
  char *receivedMessage;

  receivedMessage = Udp.getMessageFromServer(MAX_BUFFER_LENGTH);
  if (receivedMessage != NULL)
  {
    Serial.print("Empfängt: ");
    Serial.println(receivedMessage);

    // HEX Code der empfängten Daten
    for (int i = 0; i < MAX_BUFFER_LENGTH; i++)
    {
      Serial.print(receivedMessage[i],HEX);
      Serial.print(" ");
    }
      Serial.println();

    
  }
  Serial.println("running process 1");
  delay(2000);
  Serial.println("running process 2");
  delay(2000);
  Serial.println("running process 3");
  delay(2000);

}
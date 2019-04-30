#include <Arduino.h>

// needed lib
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "WifiService.h"
#include "MDClient.h"
#include "LeitSystemMessage.hpp"
#include <SoftwareSerial.h>

////////// Wifi Konfiguration /////////////
// const char *SSID = "TP-LINK_D8BA";
// const char *PASS = "35581338";
const char *SSID = "Y4NAP";
const char *PASS = "12312345";

////////// LeitSystemClient Konfigration ///////////////
const int LOCAL_LISTEN_PORT = 8080; //LeitSystemClient port
const int MAX_BUFFER_LENGTH = 20;   //Max. Länge des Pakets

IPAddress multicastIP(224, 0, 0, 0); //IP des Multicast
const int MULTICAST_PORT = 8081;     //IP des Multicast

IPAddress ServerIP(192, 168, 0, 104); //IP des Server Rechners
const int Server_PORT = 8080;         // Server Port

///////////Client Info/////////////////////
char *clientName = "MDCar1";
int id;

/////////// WIFI Und LeitSystemClient erstellen/////////
WifiService wifi(SSID, PASS);
MDClient LeitSystemClient;

/////////// Arduino signal ////////////////////////////
SoftwareSerial arduinoSerial(13, 15); //pin d7 an d8
char signal[Message::BODY_LENGTH] = {0, 0, 0, 0};
int len = 0;
char *recieved;

/////////// Server response ///////////////////////////
char response;

// Testprogramm zum Hören vom server
void setup()
{
  Serial.begin(9600);

  // NodeMCU Client setup
  wifi.connectToWifi();
  LeitSystemClient.setupListenPort(LOCAL_LISTEN_PORT);
  LeitSystemClient.connectToLeitSystemServer(multicastIP, MULTICAST_PORT);
  LeitSystemClient.registerToSystem(clientName);
  id = LeitSystemClient.getId();
  LeitSystemClient.prepareHeader();

  // Arduino serial setup
  arduinoSerial.begin(9600);
  delay(500);
}

void loop()
{
  // read from Arduino
  arduinoSerial.setTimeout(100);
  len = arduinoSerial.readBytes(signal, Message::BODY_LENGTH);
  if (len>0)
  {
    LeitSystemClient.sendSignalToServer(signal);

    //listen to server response
    while (true)
    {
      
      recieved = LeitSystemClient.getPrivateMessageFromServer(Message::MESSAGE_LENGTH);
      if (recieved != NULL && recieved[3] == 0x02)
      {
        Serial.println("Response");
        for (int i = 0; i < Message::MESSAGE_LENGTH; i++)
        {
          /* code */
          Serial.print(recieved[i], HEX);
          Serial.print(",");
        }
        Serial.println();
        response = recieved[4];
        break;
      }
      // delay(50);
    }
    arduinoSerial.write(response);
  }

  // send back clearance signal from server to arduino
}

void test1()
{
  LeitSystemClient.sendSignalToServer(Message::EXAMPLE_CARSTATE_REQ_BODY);
  delay(4000);
  char *received = LeitSystemClient.getMessageFromServer(MAX_BUFFER_LENGTH);
  if (received != NULL && received[0] == 0x11)
  {
    Serial.println(received);
    for (int i = 0; i < MAX_BUFFER_LENGTH; i++)
    {
      Serial.print(" ");
    }
    Serial.println();
  }
}
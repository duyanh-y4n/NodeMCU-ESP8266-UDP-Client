#include <Arduino.h>

// needed lib
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "WifiService.h"
#include "MDClient.h"
#include "LeitSystemMessage.hpp"
#include <SoftwareSerial.h>

////////// Wifi Konfiguration /////////////
const char *SSID = "TP-LINK_D8BA";
const char *PASS = "35581338";
// const char *SSID = "Y4NAP";
// const char *PASS = "12312345";

////////// LeitSystemClient Konfigration ///////////////
const int LOCAL_LISTEN_PORT = 8080; //LeitSystemClient port
const int MAX_BUFFER_LENGTH = 20;   //Max. Länge des Pakets

IPAddress multicastIP(224, 0, 0, 0); //IP des Multicast
const int MULTICAST_PORT = 8081;     //Port des Multicast

///////////Client Info/////////////////////
char *clientName = "MDCar1"; //max 16 chars
int id;

/////////// WIFI Und LeitSystemClient erstellen/////////
WifiService wifi(SSID, PASS);
MDClient LeitSystemClient;

/////////// Arduino signal ////////////////////////////
SoftwareSerial arduinoSerial(13, 15); //pin d7 and d8
char signal[Message::BODY_LENGTH] = {0, 0, 0, 0};
int receivedSignalLength = 0;

/////////// Server response ///////////////////////////
char *response;
char clearance;

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
  receivedSignalLength = arduinoSerial.readBytes(signal, Message::BODY_LENGTH);
  if (receivedSignalLength>0)
  {
    LeitSystemClient.sendSignalToServer(signal);

    //listen to server response
    while (true)
    {
      
      response = LeitSystemClient.getPrivateMessageFromServer(Message::MESSAGE_LENGTH);
      if (response != NULL && response[3] == 0x02)
      {
        Serial.println("Response");
        for (int i = 0; i < Message::MESSAGE_LENGTH; i++)
        {
          /* code */
          Serial.print(response[i], HEX);
          Serial.print(",");
        }
        Serial.println();
        clearance = response[Message::CLEARANCE_BYTE_POSITION_IN_MESSAGE];
        break;
      }
    }
  // send back clearance signal from server to arduino
    arduinoSerial.write(clearance);
  }
}
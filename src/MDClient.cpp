#include "MDClient.h"

MDClient::MDClient() {}

MDClient::~MDClient() {}

void MDClient::connectToLeitSystemServer(IPAddress multicastIP, int multicastPort)
{
    char *ServerInfo = new char[DEFAULT_MAX_BUFFER_LENGTH];
    Serial.println("Connecting to Server");
    Serial.println("Setup Multicast Channel");
    setupMulticastServer(multicastIP, multicastPort);
    Serial.println("Log into System...");
    while (true)
    {
        delay(1000);
        ServerInfo = getMessageFromMulticastServer(6); //4 bytes for IP, 2 bytes for port number
        if (ServerInfo != NULL)
        {
            Serial.print("Server address: ");
            Serial.print(ServerInfo[0], DEC);
            Serial.print(".");
            Serial.print(ServerInfo[1], DEC);
            Serial.print(".");
            Serial.print(ServerInfo[2], DEC);
            Serial.print(".");
            Serial.print(ServerInfo[3], DEC);
            Serial.print(":");
            this->port = (int)ServerInfo[4] * 256 + (int)ServerInfo[5];
            Serial.println(port);
            this->serverIP = new IPAddress(192, 168, 0, 104);
            setupServer(*this->serverIP, this->port);
            break;
        }

    }
    Serial.println("Connected! Can now send message to server");
    sendToServer("NodeMCU logged into system");
    delay(500);
}
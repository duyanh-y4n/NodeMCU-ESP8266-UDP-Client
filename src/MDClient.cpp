#include "MDClient.h"
#include "LeitSystemMessage.hpp"

MDClient::MDClient() {}

MDClient::~MDClient() {}

void MDClient::connectToLeitSystemServer(IPAddress multicastIP, int multicastPort)
{
    char *ServerInfo = new char[DEFAULT_MAX_BUFFER_LENGTH];
    Serial.println("Connecting to Server");
    Serial.println("Setup Multicast Channel");
    setupMulticastServer(multicastIP, multicastPort);
    Serial.println("Looking for server adress...");
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
    // sendToServer("New Client!!");
    delay(500);
}

void MDClient::registerToSystem(char* clientName){
    char *message = new char[Message::MESSAGE_LENGTH]();
    for (int i = 0; i < Message::HEADER_LENGTH; i++)
    {
        message[i] = Message::REGISTER_REQ_HEADER[i];
    }
    for (int i = 0; (i < Message::BODY_LENGTH && i<(int)strlen(clientName)); i++)
    {
        message[i+Message::HEADER_LENGTH] = clientName[i];
    }

    //Test log
    // for (int i = 0; i < Message::MESSAGE_LENGTH; i++)
    // {
        // Serial.print(message[i],HEX);
        // Serial.print(",");
    // }
    sendToServer(message,Message::MESSAGE_LENGTH);
    delete message;

    //wait for given id from server as response
    while (true)
    {
        char *received = getPrivateMessageFromServer(Message::MESSAGE_LENGTH);
        if (received != NULL && Message::isResponseFromServer(received))
        {
            this->id = received[Message::HEADER_LENGTH];
            break;
        }
    }
    
    Serial.println("Registering to server...");
    Serial.print("Client Name: ");
    Serial.println(clientName);
    Serial.print("Your ID is: ");
    Serial.print(this->id, HEX);
    Serial.println(" (in HEX)");
}
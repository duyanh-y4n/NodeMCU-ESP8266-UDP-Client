#include <MDClient.h>

MDClient::MDClient() {}

MDClient::~MDClient() {}

void MDClient::connectToLeitSystemServer(IPAddress multicastIP, int multicastPort)
{
    char *ServerInfo = new char[DEFAULT_MAX_BUFFER_LENGTH];
    IPAddress *serverIP;
    Serial.println("Connecting to Server");
    Serial.println("Setup Multicast Channel");
    setupMulticastServer(multicastIP, multicastPort);
    Serial.println("Log into server...");
    while (true)
    {
        delay(1000);
        ServerInfo = getMessageFromMulticastServer(6); //4 bytes for IP, 2 bytes for port number
        if(ServerInfo!=NULL){
        // Serial.println("Null");
        Serial.println(ServerInfo[0],DEC);
        Serial.println(ServerInfo[1],DEC);
        Serial.println(ServerInfo[2],DEC);
        Serial.println(ServerInfo[3],DEC);
        Serial.println(((int)ServerInfo[4]*256+(int)ServerInfo[5]),DEC);
        }

        // break;
    }

    Serial.println("connected");
    // Serial.printf("connecting to: %d %d %d %d %d\n", ServerInfo[0], ServerInfo[1], ServerInfo[2], ServerInfo[3],
    //   (ServerInfo[4] * 256 + ServerInfo[5]));
    // serverIP = new IPAddress(83, 2, 186, 1);
    // setupServer(*serverIP,8080);
    // sendToServer("Hi");
}
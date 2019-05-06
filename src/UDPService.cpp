#include "UDPService.h"

UDPService::UDPService()
{
    this->serverPort = DEFAULT_PORT;
}

UDPService::~UDPService()
{
}

void UDPService::setupListenPort(int listenPort)
{
    this->listenPort = listenPort;
    this->Udp.begin(this->listenPort);
}

void UDPService::setupServer(IPAddress serverHostIp, int serverPort)
{
    this->serverHostIp = serverHostIp;
    this->serverPort = serverPort;
}

bool UDPService::sendToServer(char *stringBuffer)
{
    bool sendingSuccessful = this->Udp.beginPacket(this->serverHostIp, this->serverPort);
    if (sendingSuccessful)
    {
        // Serial.println("sending success");
        this->Udp.write(stringBuffer);
        this->Udp.endPacket();
    }
    else
    {
        Serial.println("send failed");
    }
    return sendingSuccessful;
};

bool UDPService::sendToServer(char *buffer, int bufferLength){
    bool sendingSuccessful = this->Udp.beginPacket(this->serverHostIp, this->serverPort);
    if (sendingSuccessful)
    {
        // Serial.println("sending success");
        for (int i = 0; i < 20; i++)
        {
            this->Udp.write(buffer[i]);
        }
        
        this->Udp.endPacket();
    }
    else
    {
        Serial.println("send failed");
    }
    return sendingSuccessful;
}

char* UDPService::getPrivateMessageFromServer(int bufferLength)
{
    int packetSize = this->Udp.parsePacket();
    char *incomingPacket = new char[DEFAULT_MAX_BUFFER_LENGTH];
    if (packetSize)
    {
        // Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
        Serial.println();
        int receivedBytesLength = this->Udp.read(incomingPacket, bufferLength);
        if (receivedBytesLength > 0)
        {
            cleanUnnecessaryDataBytes(incomingPacket, receivedBytesLength, bufferLength);
        }
        // Serial.printf("UDP packet content: %s\n", incomingPacket);
        return incomingPacket;
    }
    delete [] incomingPacket;
    return NULL;
};

void UDPService::setupMulticastServer(IPAddress multicastHostIp, int multicastPort)
{
    *this->multicastHostIp = multicastHostIp;
    this->multicastPort = multicastPort;
    this->UdpMulti.beginMulticast(WiFi.localIP(), this->multicastHostIp, this->multicastPort);
};

char* UDPService::getMessageFromMulticastServer(int bufferLength)
{
    int packetSize = this->UdpMulti.parsePacket();
    char *incomingPacket = new char[DEFAULT_MAX_BUFFER_LENGTH];
    if (packetSize)
    {
        // Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
        int receivedBytesLength = this->UdpMulti.read(incomingPacket, bufferLength);
        if (receivedBytesLength > 0)
        {
            cleanUnnecessaryDataBytes(incomingPacket, receivedBytesLength, bufferLength);
        }
        // Serial.printf("UDP Paket content: %s\n", incomingPacket);
        return incomingPacket;
    }
    delete [] incomingPacket;
    return NULL;
}

char* UDPService::getMessageFromServer(int bufferLength)
{
    //last initiated message will have higher priority and be caught
    char *receivedMulti = getMessageFromMulticastServer(bufferLength);
    char *receivedPrivate = getPrivateMessageFromServer(bufferLength);
    if (receivedPrivate != NULL)
    {
        return receivedPrivate;
    }
    if (receivedMulti != NULL)
    {
        return receivedMulti;
    }
    return NULL;
}

WiFiUDP UDPService::getUdp()
{
    return this->Udp;
}

//TODO: create lib for processing raw data, add this function to it
void UDPService::cleanUnnecessaryDataBytes(char *data, int beginPos, int endPos)
{
    for (int i = beginPos; i < endPos; i++)
    {
        /* code */
        data[i] = 0;
    }
}
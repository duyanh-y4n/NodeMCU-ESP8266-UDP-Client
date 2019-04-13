#include <UDPService.h>

UDPService::UDPService()
{
    // this->serverHostIp = new IPAddress(0,0,0,0);
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

void UDPService::sendToServer(char buffer[])
{
    if (!this->Udp)
    {
        this->Udp.beginPacket(*this->serverHostIp, this->serverPort);
        this->Udp.write(buffer);
        this->Udp.endPacket();
    }
};

char *UDPService::getPrivateMessageFromServer(int bufferLength)
{
    //TODO: refactor, get from server
    int packetSize = this->Udp.parsePacket();
    char *incomingPacket = new char[DEFAULT_MAX_BUFFER_LENGTH];
    if (packetSize)
    {
        // Serial.printf("Empfängt %d bytes von %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
        Serial.println();
        int receivedBytesLength = this->Udp.read(incomingPacket, bufferLength);
        if (receivedBytesLength > 0)
        {
            cleanUnnecessaryDataBytes(incomingPacket, receivedBytesLength, bufferLength);
        }
        // Serial.printf("UDP Paket Inhalt: %s\n", incomingPacket);
        return incomingPacket;
    }
    return NULL;
};

void UDPService::setupMulticastServer(IPAddress multicastHostIp, int multicastPort)
{
    this->multicastHostIp = multicastHostIp;
    this->multicastPort = multicastPort;
    this->UdpMulti.beginMulticast(WiFi.localIP(), this->multicastHostIp, this->multicastPort);
};

char *UDPService::getMessageFromMulticastServer(int bufferLength)
{
    int packetSize = this->UdpMulti.parsePacket();
    char *incomingPacket = new char[DEFAULT_MAX_BUFFER_LENGTH];
    if (packetSize)
    {
        // Serial.printf("Empfängt %d bytes von %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
        int receivedBytesLength = this->UdpMulti.read(incomingPacket, bufferLength);
        if (receivedBytesLength > 0)
        {
            cleanUnnecessaryDataBytes(incomingPacket,receivedBytesLength,bufferLength);
        }
        // Serial.printf("UDP Paket Inhalt: %s\n", incomingPacket);
        return incomingPacket;
    }
    return NULL;
}

char *UDPService::getMessageFromServer(int bufferLength)
{
    //last initiated message will have higher priority and be caught
    char* receivedMulti = getMessageFromMulticastServer(bufferLength);
    char* receivedPrivate = getPrivateMessageFromServer(bufferLength);
    if (receivedMulti != NULL)
    {
        return receivedMulti;
    }
    if (receivedPrivate != NULL)
    {
        return receivedPrivate;
    }
    return NULL;
}

WiFiUDP UDPService::getUdp()
{
    return this->Udp;
}


//TODO: create bibliothek for processing raw data, add this function to it
void UDPService::cleanUnnecessaryDataBytes(char* data, int beginPos, int endPos){
    for (int i = beginPos; i < endPos; i++)
    {
        /* code */
        data[i] = 0;
    }
}
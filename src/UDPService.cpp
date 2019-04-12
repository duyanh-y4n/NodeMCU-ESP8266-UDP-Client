#include<UDPService.h>


UDPService::UDPService()
{
    // this->serverHostIp = new IPAddress(0,0,0,0);
    this->serverPort = DEFAULT_PORT;
}

UDPService::~UDPService()
{
}

void UDPService::setupListenPort(int listenPort){
    this->listenPort = listenPort;
    this->Udp.begin(this->listenPort);
}

void UDPService::setupServer(IPAddress serverHostIp, int serverPort)
{
    *this->serverHostIp = serverHostIp;
    this->serverPort = serverPort;
}

void UDPService::sendToServer(char buffer[])
{
    if(this->Udp!=NULL){
    this->Udp.beginPacket(*this->serverHostIp, this->serverPort);
    this->Udp.write(buffer);
    this->Udp.endPacket();
    }
};

char* UDPService::getMessageFromServer(int bufferLength)
{
    //TODO: refactor, get from server
    int packetSize = this->Udp.parsePacket();
    char incomingPacket[255];
    if (packetSize)
    {
        Serial.printf("Empfängt %d bytes von %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
        int len = this->Udp.read(incomingPacket, bufferLength);
        if (len > 0)
        {
            incomingPacket[len] = 0;
        }
        Serial.printf("UDP Paket Inhalt: %s\n", incomingPacket);
    }
    return incomingPacket;
};

void UDPService::setupMulticastServer(IPAddress multicastHostIp, int multicastPort){
    *this->multicastHostIp = multicastHostIp;
    this->multicastPort = multicastPort;
    IPAddress multicastAddress();
    this->Udp.beginMulticast(WiFi.localIP(),*this->multicastHostIp,this->multicastPort);
};

WiFiUDP UDPService::getUdp(){
    return this->Udp;
}
#include <UDPTestLogger.h>

UDPTestLogger::UDPTestLogger(int serialBaudRate, UDPService udpService)
{
    this->serialBaudRate = serialBaudRate;
    this->udpService = udpService;
    Serial.begin(this->serialBaudRate);
    Serial.printf("Start UDP Test Logger at %d\n", this->serialBaudRate);
}

UDPTestLogger::~UDPTestLogger()
{

};

void UDPTestLogger::printLocalHostInfo(){
    Serial.printf("Lokale IP %s, port %d\n", WiFi.localIP().toString().c_str(), this->udpService.getUdp().remotePort());
}


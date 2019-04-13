#include <Arduino.h>
#include <UDPService.h>


//TODO: still dont know if i need this class :/
class UDPTestLogger
{
private:
    /* data */
    int serialBaudRate;
    UDPService udpService;
public:
    UDPTestLogger(int serialBaudRate, UDPService udpService);
    ~UDPTestLogger();

    void printMulticastServerInfo();
    void printServerInfo();
    void printLocalHostInfo();
};
#include <Arduino.h>
#include <UDPService.h>

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
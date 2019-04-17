#include"UDPService.h"
#include<WiFiClient.h>

class MDClient:public UDPService
{
private:
    /* data */
    IPAddress *serverIP;
    int port;
public:
    MDClient(/* args */);
    ~MDClient();
    void connectToLeitSystemServer(IPAddress multicastIP, int multicastPort);
};

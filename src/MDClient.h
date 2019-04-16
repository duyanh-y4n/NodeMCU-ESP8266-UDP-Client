#include<UDPService.h>
#include<WiFiClient.h>

class MDClient:public UDPService
{
private:
    /* data */
public:
    MDClient(/* args */);
    ~MDClient();
    void connectToLeitSystemServer(IPAddress multicastIP, int multicastPort);
};

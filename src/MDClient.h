#include"UDPService.h"
#include<WiFiClient.h>

class MDClient:public UDPService
{
private:
    /* data */
    IPAddress *serverIP;
    int port;
    unsigned short id;
    char name[16];
    char header[4];
public:
    MDClient(/* args */);
    ~MDClient();
    void connectToLeitSystemServer(IPAddress multicastIP, int multicastPort);
    void registerToSystem(char *clientName);
    char getId();
    void prepareHeader();
    void sendSignalToServer(char* carState);
    void showMessage(char *message);
};

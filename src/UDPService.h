#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
const int DEFAULT_PORT = 8080;

class UDPService
{
  private:
    IPAddress *serverHostIp;
    int serverPort;
    IPAddress *multicastHostIp;
    int multicastPort;
    WiFiUDP Udp;
    int listenPort;

  public:
    UDPService();
    ~UDPService();

    WiFiUDP getUdp();

    void setupListenPort(int listenPort);

    void setupServer(IPAddress serverHostIp, int serverPort);
    void sendToServer(char buffer[]);
    char* getMessageFromServer(int bufferLength);

    void setupMulticastServer(IPAddress multicastHostIp, int MulticastPort);
    char* getMessageFromMulticastServer(int bufferLength);
};

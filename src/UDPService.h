#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
const int DEFAULT_PORT = 8080;
const int DEFAULT_MAX_BUFFER_LENGTH = 255;

class UDPService
{
  private:
    IPAddress serverHostIp;
    int serverPort;
    IPAddress multicastHostIp;
    int multicastPort;
    WiFiUDP Udp;
    WiFiUDP UdpMulti;
    int listenPort;

  public:
    UDPService();
    ~UDPService();

    WiFiUDP getUdp();

    void setupListenPort(int listenPort);

    void setupServer(IPAddress serverHostIp, int serverPort);
    void sendToServer(char buffer[]);
    char* getPrivateMessageFromServer(int bufferLength); //private message to one client only

    void setupMulticastServer(IPAddress multicastHostIp, int MulticastPort);
    char* getMessageFromMulticastServer(int bufferLength);

    char* getMessageFromServer(int bufferLength);
};

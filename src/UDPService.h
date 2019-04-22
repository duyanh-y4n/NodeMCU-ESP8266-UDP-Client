#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define DEFAULT_PORT 8080
#define DEFAULT_MAX_BUFFER_LENGTH 30

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
    bool sendToServer(char *buffer); //use this to send string
    bool sendToServer(char *buffer, int bufferLength);
    char* getPrivateMessageFromServer(int bufferLength); //private message to one client only

    void setupMulticastServer(IPAddress multicastHostIp, int MulticastPort);
    char* getMessageFromMulticastServer(int bufferLength);

    char* getMessageFromServer(int bufferLenght);

    void cleanUnnecessaryDataBytes(char* data, int beginPos, int endPos);
};

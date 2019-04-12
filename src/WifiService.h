#include <ESP8266WiFi.h>

class WifiService
{
  private:
    /* data */
    const char *ssid;
    const char *password;

  public:
    WifiService(/* args */);
    WifiService(const char *ssid, const char *password);
    ~WifiService();

    void connectToWifi();
    void printConnectionInfo();
};

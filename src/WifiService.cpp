#include "WifiService.h"


//TODO: refactor, remove all serial print command
// this class is a core class, should not have any print
WifiService::WifiService(/* args */)
{
    this->ssid = "";
    this->password = "";
}

WifiService::WifiService(const char *ssid, const char *password)
{
    this->ssid = ssid;
    this->password = password;
}

WifiService::~WifiService()
{
}

void WifiService::connectToWifi()
{
    Serial.println();
    Serial.print("Connecting to AP with SSID=");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    /*Solange keine Verbindung zu einem AccessPoint (AP) aufgebaut wurde*/
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    printConnectionInfo();
}

void WifiService::printConnectionInfo()
{
    Serial.print("Connected! IP: ");
    Serial.println(WiFi.localIP());
    /*Signalstärke des AP*/
    long rssi = WiFi.RSSI();
    Serial.print("Signal strength of this AP:");
    Serial.print(rssi);
    Serial.println(" dBm");
    Serial.println();
}
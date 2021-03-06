#include "MDClient.h"
#include "LeitSystemMessage.cpp"

MDClient::MDClient() {}

MDClient::~MDClient() {}

void MDClient::connectToLeitSystemServer(IPAddress multicastIP, int multicastPort)
{
    char *ServerInfo = new char[DEFAULT_MAX_BUFFER_LENGTH];
    Serial.println("Connecting to Server");
    Serial.println("Setup Multicast Channel");
    setupMulticastServer(multicastIP, multicastPort);
    Serial.println("Looking for server adress...");
    while (true)
    {
        delay(100);
        ServerInfo = getMessageFromMulticastServer(6); //4 bytes for IP, 2 bytes for port number
        if (ServerInfo != NULL)
        {
            Serial.print("Server address: ");
            Serial.print(ServerInfo[0], DEC);
            Serial.print(".");
            Serial.print(ServerInfo[1], DEC);
            Serial.print(".");
            Serial.print(ServerInfo[2], DEC);
            Serial.print(".");
            Serial.print(ServerInfo[3], DEC);
            Serial.print(":");
            this->port = (int)ServerInfo[4] * 256 + (int)ServerInfo[5];
            Serial.println(port);
            this->serverIP = new IPAddress(ServerInfo[0], ServerInfo[1], ServerInfo[2], ServerInfo[3]);
            setupServer(*this->serverIP, this->port);
            break;
        }
    }
    Serial.println("Connected! Can now send message to server");
    // sendToServer("New Client!!");
    delay(100);
}

void MDClient::registerToSystem(char *clientName)
{
    char message[Message::MESSAGE_LENGTH] = {0};
    Serial.println("Registering to server...");
    Serial.println(message);
    Serial.print("Client Name: ");
    Serial.println(clientName);
    for (int i = 0; i < Message::HEADER_LENGTH; i++)
    {
        message[i] = Message::REGISTER_REQ_HEADER[i];
    }
    for (int i = 0; (i < Message::BODY_LENGTH && i < (int)strlen(clientName)); i++)
    {
        if (clientName[i] == 0)
            break;
        message[i + Message::HEADER_LENGTH] = clientName[i];
    }

    // Test log
    Serial.println("Sending Register request");
    showMessage(message, Message::MESSAGE_LENGTH);

    sendToServer(message, Message::MESSAGE_LENGTH);

    //wait for given id from server as response
    while (true)
    {
        char *received = getPrivateMessageFromServer(Message::MESSAGE_LENGTH);
        if (received != NULL && Message::isRegisterResponseFromServer(received))
        {
            this->id = received[Message::HEADER_LENGTH];
            break;
        }
    }

    Serial.print("Your ID is: ");
    Serial.print(this->id, HEX);
    Serial.println(" (in HEX)");
    Serial.println();
}

char MDClient::getId()
{
    return this->id;
}

void MDClient::prepareHeader()
{
    for (int i = 0; i < Message::HEADER_LENGTH; i++)
    {
        this->header[i] = Message::DEFAULT_CARSTATE_REQ_HEADER[i];
    }
    this->header[2] = this->id;
}

void MDClient::sendSignalToServer(char *carState)
{
    char message[Message::MESSAGE_LENGTH] = {0};
    char signalBody[Message::CAR_STATE_BODY_LENGTH];
    prepareSignalBody(carState, signalBody);
    cleanUnnecessaryDataBytes(message, Message::HEADER_LENGTH, Message::MESSAGE_LENGTH);
    Serial.println();
    Serial.println("Sending carState to server");

    for (int i = 0; i < Message::HEADER_LENGTH; i++)
    {
        message[i] = this->header[i];
    }
    for (int i = 0; i < Message::CAR_STATE_BODY_LENGTH; i++)
    {
        message[Message::HEADER_LENGTH + i] = signalBody[i];
    }
    showMessage(message, Message::MESSAGE_LENGTH);
    Serial.println("Original raw car state from arduino:");
    showMessage(carState, Message::CAR_STATE_LENGTH);
    sendToServer(message, Message::MESSAGE_LENGTH);
    //delete message;
}

void MDClient::showMessage(char *message, int length)
{
    for (int i = 0; i < length; i++)
    {
        Serial.print(message[i], HEX);
        Serial.print(",");
    }
    Serial.println();
}

void MDClient::prepareSignalBody(char *carState, char *signalBody)
{
    char blinker = carState[4];
    char geschwindigkeit = carState[5];
    int Position = 0xFF;
    bool found;
    for (int z = 0; z < 20; z++)
    {
        for (int u = 0; u < 5; u++)
        {
        found = true;
            for (int i = 0; i < 4; i++)
            {
                if ((byte)carState[i] != (byte)Message::RFID[z][u][i])
                {
                    found = false;
                    break;
                }
            }
            if(found == false) continue;
            Position = z;
            break;
        }
        if (Position != 0xFF)
        {
            break;
        }
    }
    
    switch (Position)
    {
    case 0:
        signalBody[0] = (char)0xA0;
        break;
    case 1:
        signalBody[0] = (char)0xA1;
        break;
    case 2:
        signalBody[0] = (char)0xA2;
        break;
    case 3:
        signalBody[0] = (char)0xA3;
        break;
    case 4:
        signalBody[0] = (char)0xA4;
        break;
    case 5:
        signalBody[0] = (char)0xA5;
        break;
    case 6:
        signalBody[0] = (char)0xA6;
        break;
    case 7:
        signalBody[0] = (char)0xA7;
        break;
    case 8:
        signalBody[0] = (char)0xB0;
        break;
    case 9:
        signalBody[0] = (char)0xB1;
        break;
    case 10:
        signalBody[0] = (char)0xB2;
        break;
    case 11:
        signalBody[0] = (char)0xB4;
        break;
    case 12:
        signalBody[0] = (char)0xB5;
        break;
    case 13:
        signalBody[0] = (char)0xB6;
        break;
    case 14:
        signalBody[0] = (char)0xC0;
        break;
    case 15:
        signalBody[0] = (char)0xC1;
        break;
    case 16:
        signalBody[0] = (char)0xC3;
        break;
    case 17:
        signalBody[0] = (char)0xC4;
        break;
    case 18:
        signalBody[0] = (char)0xC5;
        break;
    case 19:
        signalBody[0] = (char)0xC7;
        break;
    default:
        signalBody[0] = (char)0xFF;
        break;
    }

    signalBody[1] = blinker;
    signalBody[2] = geschwindigkeit;
}
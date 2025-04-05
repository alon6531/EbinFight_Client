#pragma once

#include "Globals.h"


class Client
{
public:
    Client();
    void Init();
    bool connect();
    void reconnect();
    void sendMessage(const std::string& message);
    void receiveMessages();
    void Disconnect();

private:
    sf::TcpSocket m_socket;
    std::string m_serverIp;
    unsigned short m_serverPort;
    int m_reconnCounter;
};
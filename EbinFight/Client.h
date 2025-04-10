#pragma once

#include "Globals.h"

class Client
{
public:
    Client(const std::string& username);
    void Init();
    bool connect();
    void reconnect();
    void sendMessage(const std::string& message);
    const std::string& receiveMessages();
    void sendMessageUDP(const std::string& message);
    std::string receiveMessageUDP();
    const std::string& receiveLargeMessages();
    void Disconnect();

    void InitUser();
    void InitPlayer(json player_data);
	void UpdatePlayer(json player_data);
	json ReceiveAllPlayers();
    json ReceivePlayer();
    json ReciveMapData();

private:
    std::string m_username;
    sf::TcpSocket m_socket;
    std::string m_serverIp;
    unsigned short m_serverPort;
    sf::UdpSocket m_udpSocket;
    int m_reconnCounter;
};
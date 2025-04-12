#pragma once

#include "Globals.h"


class Client
{
public:
    Client();
	~Client() = default;
	void Start();
    bool connect();
    void Disconnect();


    const std::string& getUsername() const { return m_username; }

    void InitUser(const std::string& username);
    void InitPlayer(json player_data);
	void UpdatePlayer(json player_data);

	json ReceiveAllPlayers();
    json ReceivePlayer();
    json ReciveMapData();

	


private:
    void Init();
    void sendMessageTCP(const std::string& message);
    const std::string& receiveMessagesTCP();
    void sendMessageUDP(const std::string& message);
    std::string receiveMessageUDP();
    const std::string& receiveLargeMessages();

private:
    std::string m_username;

    sf::TcpSocket m_socket;
    std::optional<sf::IpAddress> m_serverIp;
    unsigned short m_serverPort;

    sf::UdpSocket m_udpSocket;

    int m_reconnCounter;
};
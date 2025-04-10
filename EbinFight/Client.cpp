#include "Client.h"
#include <iostream>


Client::Client(const std::string& username)
{
	m_username = username;
    m_udpSocket.setBlocking(false);
    m_reconnCounter = 5;
}

void Client::Init()
{
  
    std::vector<std::string> lines;
    if (OpenFile(lines, "..\\Configs\\Client.txt"))
    {

        try {
            m_serverIp = lines[0];
            m_serverPort = static_cast<short>(std::stoi(lines[1]));
            m_reconnCounter = static_cast<int>(std::stoi(lines[2]));
        }
        catch (const std::exception& e) {
            std::cerr << "Client:Error parsing configuration: " << e.what() << std::endl;
            // You c
        }
        std::cout << "Client:serverIp: " << m_serverIp << "\n";
        std::cout << "Client:serverPort: " << m_serverPort << "\n";
    }
}



bool Client::connect()
{
    this->Init();
    
    std::uint32_t ip = IpToUint32_t(m_serverIp);
    
    sf::Socket::Status status = m_socket.connect(sf::IpAddress(ip), m_serverPort);
    if (status != sf::Socket::Status::Done)
    {
        std::cerr << "Client:Failed to connect to server.\n";
        return false;
    }
    this->InitUser();
    std::cout << "Client: " << m_username <<"Connected to server at " << m_serverIp << ":" << m_serverPort << "\n";
    return true;
}

void Client::InitUser()
{
	json send = {
		   {"action", "InitUser"},
		   {"data", m_username}
	};
	this->sendMessage(send.dump());
}

void Client::reconnect()
{
    
    std::cout << "Client:Attempting to reconnect...\n";
    while (!connect() && m_reconnCounter > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(2));  // Pause 5 seconds before retry
        m_reconnCounter--;
    }

    std::cout << "Client:faild to reconnect: \n";
    this->Disconnect();
   
   
   
}

void Client::sendMessage(const std::string& message)
{
    try {
        sf::Socket::Status status = m_socket.send(message.c_str(), message.size());
        if (status != sf::Socket::Status::Done)
        {
            throw std::runtime_error("Client:Failed to send message");
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        if (e.what() == std::string("Client:Failed to send message")) {
            // Try to reconnect if sending fails
            //this->reconnect();
        }
    }
}

const std::string& Client::receiveMessages()
{
    try {
        char buffer[1024];
        std::size_t received;
        sf::Socket::Status status = m_socket.receive(buffer, sizeof(buffer), received);

        if (status == sf::Socket::Status::Done)
        {
            std::string message(buffer, received);
            std::cout << "Client:Server: " << message << "\n";

            
            return *new std::string(message);
        }
        else if (status == sf::Socket::Status::Disconnected)
        {
            throw std::runtime_error("Client:Disconnected from server");
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        if (e.what() == std::string("Client:Disconnected from server")) {
            this->reconnect(); // Attempt to reconnect on disconnect
        }
    }
}

void Client::sendMessageUDP(const std::string& message)
{
    try {
        // הפונקציה `send` ב-SFML 3 ל-UDP השתנתה להיות על פי פרמטרים חדשים
    
        sf::IpAddress serverIp(IpToUint32_t(m_serverIp));
        unsigned short serverPort = m_serverPort;
        std::cout << "Sending UDP message to: " << m_serverIp << ":" << m_serverPort << "\n";  // הדפסה לוג
        // שלח את ההודעה לשרת ב-UDP
        sf::Socket::Status status = m_udpSocket.send(message.c_str(), message.size(), serverIp, serverPort);
        if (status != sf::Socket::Status::Done) {
            throw std::runtime_error("Client: Failed to send UDP message");
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        this->reconnect();
    }
}

std::string Client::receiveMessageUDP()
{
    try {
        char buffer[1024];
        std::size_t received;
        std::optional<sf::IpAddress> sender;
        unsigned short senderPort;

        m_udpSocket.bind(m_serverPort);  // קבע את הפורט של ה-UDP
        m_udpSocket.setBlocking(false);  // שמור על חיבור לא חסום
       
        // קבלה של הודעה ב-UDP
        sf::Socket::Status status = m_udpSocket.receive(buffer, sizeof(buffer), received, sender, senderPort);
        if (status == sf::Socket::Status::Done) {
            std::string message(buffer, received);
            std::cout << "Client: Received from UDP: " << message << "\n";
            return message;
        }
        else if (status == sf::Socket::Status::Disconnected) {
            throw std::runtime_error("Client: Disconnected from UDP server");
        }
		else if (status == sf::Socket::Status::Error) {
			throw std::runtime_error("Client: Error receiving UDP message");
		}
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        this->reconnect();
    }

    return "";
}

const std::string& Client::receiveLargeMessages()
{
    try {
        char buffer[65536];
        std::size_t received;
        sf::Socket::Status status = m_socket.receive(buffer, sizeof(buffer), received);

        if (status == sf::Socket::Status::Done)
        {
            std::string message(buffer, received);
            std::cout << "Client:Server: " << message << "\n";


            return *new std::string(message);
        }
        else if (status == sf::Socket::Status::Disconnected)
        {
            throw std::runtime_error("Client:Disconnected from server");
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        if (e.what() == std::string("Client:Disconnected from server")) {
            this->reconnect(); // Attempt to reconnect on disconnect
        }
    }
}

void Client::Disconnect()
{
    std::cout << "Client:client disconnecting..." << "\n";
    m_socket.disconnect();
}

json Client::ReciveMapData()
{
    json send = {
		{"action", "SendMapData"}
	};
	this->sendMessage(send.dump());
	std::string message = this->receiveLargeMessages();
	json mapData;
	try {
		mapData = json::parse(message);
	}
	catch (const std::exception& e) {
		std::cerr << "Client:ReciveMapData:Error parsing JSON: " << e.what() << "\n";
		return nullptr;
	}
	return mapData;
}

void Client::InitPlayer(json player_data)
{
    json send = {
        {"action", "InitPlayer"},
        {"data", player_data}
    };
    this->sendMessage(send.dump());
    std::string message = this->receiveMessages();
    json player;
    try {
        player = json::parse(message);
    }
    catch (const std::exception& e) {
        std::cerr << "Client:InitPlayer:Error parsing JSON: " << e.what() << "\n";
        return;
    }
    std::cout << "Client:InitPlayer: " << player.dump() << "\n";
}

void Client::UpdatePlayer(json player_data)
{
    json send = {
		{"action", "UpdatePlayer"},
		{"data", player_data}
    };
	this->sendMessageUDP(send.dump());
}

json Client::ReceivePlayer()
{
    json send = {
        {"action", "SendPlayer"}
    };
    this->sendMessage(send.dump());
    std::string message = this->receiveMessages();
    json player;
    try {
        player = json::parse(message);
		std::cout << "Client:ReceivePlayer: " << player.dump() << "\n";
        return player;
    }
    catch (const std::exception& e) {
        std::cerr << "Client:InitPlayer:Error parsing JSON: " << e.what() << "\n";
        return json::object();
    }
   
}



#include "Client.h"
#include "Engine.h"


Client::Client(const std::string& username)
	: m_username(username)
{
}

void Client::Start()
{
    this->Init();

	if (this->connect())
	{
		Engine* app = new Engine(*this);
		app->Run();
        delete app;
	}
}

void Client::Init()
{
  
    std::vector<std::string> lines;
    if (OpenFile(lines, "..\\Configs\\Client.txt"))
    {

        try {

            m_serverIp = sf::IpAddress(IpToUint32_t(lines[0]));
            m_serverPort = static_cast<short>(std::stoi(lines[1]));
            m_reconnCounter = static_cast<int>(std::stoi(lines[2]));
        }
        catch (const std::exception& e) {
            std::cerr << "Client:Error parsing configuration: " << e.what() << std::endl;
            // You c
        }
        std::cout << "Client:serverIp: " << m_serverIp.value() << "\n";
        std::cout << "Client:serverPort: " << m_serverPort << "\n";
    }

    m_udpSocket.setBlocking(false);

    m_reconnCounter = 5;
}

bool Client::connect()
{
   
	if (!m_serverIp.has_value() || m_serverPort == 0)
	{
		std::cerr << "Client:Invalid server IP or port.\n";
		return false;
	}


    sf::Socket::Status status = m_socket.connect(m_serverIp.value(), m_serverPort);
    if (status != sf::Socket::Status::Done)
    {
        std::cerr << "Client:Failed to connect to server.\n";
        return false;
    }


    this->InitUser();
    std::cout << "Client: " << m_username <<" Connected to server at " << m_serverIp.value().toString() << ":" << m_serverPort << "\n";
    return true;
}

void Client::InitUser()
{
	json send = {
		   {"action", "InitUser"},
		   {"data", m_username}
	};
	this->sendMessageTCP(send.dump());
}



void Client::sendMessageTCP(const std::string& message)
{
    try {
        sf::Socket::Status status = m_socket.send(message.c_str(), message.size());
        if (status != sf::Socket::Status::Done)
        {
            throw std::runtime_error("Client:Failed to send message");
        }
		std::cout << "Client:Sent message: " << message << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        if (e.what() == std::string("Client:Failed to send message")) {
            // Try to reconnect if sending fails
            //this->reconnect();
        }
    }
}

const std::string& Client::receiveMessagesTCP()
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
            throw std::runtime_error("Client:receiveMessagesTCP::Disconnected from server");
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        if (e.what() == std::string("Client:receiveMessagesTCP::Disconnected from server")) {
        }
    }
}

void Client::sendMessageUDP(const std::string& message)
{
    try {
        // הפונקציה `send` ב-SFML 3 ל-UDP השתנתה להיות על פי פרמטרים חדשים
    
        unsigned short serverPort = m_serverPort;
        std::cout << "Sending UDP message to: " << m_serverIp.value().toString() << ":" << m_serverPort << "\n";  // הדפסה לוג
        // שלח את ההודעה לשרת ב-UDP
        sf::Socket::Status status = m_udpSocket.send(message.c_str(), message.size(), m_serverIp.value(), serverPort);
        if (status != sf::Socket::Status::Done) {
            throw std::runtime_error("Client: Failed to send UDP message");
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }
}

std::string Client::receiveMessageUDP()
{
    char buffer[1024];
    std::size_t received;
    std::optional<sf::IpAddress> sender;
    unsigned short senderPort;

    sf::Socket::Status status = m_udpSocket.receive(buffer, sizeof(buffer), received, sender, senderPort);

    if (status == sf::Socket::Status::Done)
    {
        std::string message(buffer, received);
        std::cout << "Client: Received UDP message from " << sender.value().toString() << ":" << senderPort << " - " << message << "\n";
        return message;
    }
    else if (status == sf::Socket::Status::NotReady)
    {
        // Non-blocking socket has no data right now.
        return "";
    }
    else if (status == sf::Socket::Status::Disconnected)
    {
        std::cerr << "Client: Disconnected from server (UDP)\n";
        return "";
    }
    else if (status == sf::Socket::Status::Error)
    {
        std::cerr << "Client: Error receiving UDP data\n";
        return "";
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
	this->sendMessageTCP(send.dump());

	std::string received = this->receiveLargeMessages();
	try {
        json mapData = json::parse(received);
		std::cout << "Client: Map received successfully" << "\n";
        return mapData;
	}
	catch (const std::exception& e) {
		std::cerr << "Client:ReciveMapData:Error parsing JSON: " << e.what() << "\n";
		return json::object();
	}
	
}

void Client::InitPlayer(json player_data)
{
    json send = {
        {"action", "InitPlayer"},
        {"data", player_data}
    };
    this->sendMessageTCP(send.dump());
}

void Client::UpdatePlayer(json player_data)
{
    json send = {
		{"username", m_username},
		{"action", "UpdatePlayer"},
		{"data", player_data}
    };
	this->sendMessageUDP(send.dump());
}

json Client::ReceiveAllPlayers()
{
    json send = {
        {"username", m_username},
        {"action", "SendAllPlayers"}
    };

    // Send the request to the server via UDP
    this->sendMessageUDP(send.dump());

    // Receive the response from the server
    std::string message = this->receiveMessageUDP();
	if (message.empty()) {
		std::cerr << "Client:ReceiveAllPlayers: No Players Found\n";
		return json::object();
	}
    std::cout << "Client: ReceiveAllPlayers: " << message << "\n";

    // Parse and handle the response (optional - you can improve this depending on the server's response)
    try {
        json response = json::parse(message);
        
        return response;
       
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing response: " << e.what() << "\n";
        return json::object();
    }
}

json Client::ReceivePlayer()
{
    json send = {
        {"action", "SendPlayer"},
	  
    };
    this->sendMessageTCP(send.dump());
    std::string message = this->receiveMessagesTCP();
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



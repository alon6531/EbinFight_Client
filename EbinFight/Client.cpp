#include "Client.h"
#include <iostream>


Client::Client() 
{
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
    std::cout << "Client:Connected to server at " << m_serverIp << ":" << m_serverPort << "\n";
    return true;
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
            this->reconnect();
        }
    }
}

void Client::receiveMessages()
{
    try {
        char buffer[1024];
        std::size_t received;
        sf::Socket::Status status = m_socket.receive(buffer, sizeof(buffer), received);

        if (status == sf::Socket::Status::Done)
        {
            std::string message(buffer, received);
            std::cout << "Client:Server: " << message << "\n";
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

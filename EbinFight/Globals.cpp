#include "Globals.h"

sf::Font Global::font = sf::Font("..\\arial.ttf");
unsigned int Global::win_width = 0;
unsigned int Global::win_height = 0;

std::uint32_t IpToUint32_t(const std::string& ip)
{
    uint32_t result = 0;
    std::stringstream ss(ip);
    std::string token;
    int shift = 24;  // Start with the most significant byte

    while (std::getline(ss, token, '.')) {
        result |= (std::stoi(token) << shift);  // Shift each byte to its correct position
        shift -= 8;  // Move to the next byte
    }


    return result;
}

bool OpenFile(std::vector<std::string>& lines, const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Globals:ERROR::CANT_OPEN_FILE: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            line.erase(0, pos + 1);
        }

        // Trim spaces (optional)
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        // Skip empty lines
        if (line.empty()) continue;

        lines.push_back(line);
    }

    std::cout << "Globals:read from file: \"" << filename << "\" successful" << std::endl;
    return true;
}


const std::string& Package::Pack(const std::string& action, const std::string& data)
{
    return action + "|" + data;
}

const std::map<std::string, std::string>& Package::Unpack(const std::string& massage) 
{
    std::map<std::string, std::string> result;

    size_t pos = massage.find('|');
    if (pos != std::string::npos) {
        result["action"] = massage.substr(0, pos);
        result["data"] = massage.substr(pos + 1);
    }
    else {
        result["action"] = "";
        result["data"] = "";
    }

    return result;
}



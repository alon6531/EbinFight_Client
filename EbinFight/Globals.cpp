#include "Globals.h"

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
        file.close();
        return false;
    }

    std::string line;

    // Process the file
    while (std::getline(file, line)) {
        size_t pos = line.find("=");
        if (pos != std::string::npos) {
            // Erase everything up to and including the '=' sign
            line.erase(0, pos + 1);
        }

        // Process the modified line (for example, print it)
        lines.push_back(line);
    }
    std::cout << "Globals:read from file: \""<< filename << "\" secsseful" << std::endl;

    file.close();
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



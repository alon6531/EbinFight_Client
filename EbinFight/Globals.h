#pragma once
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <thread>
#include <stdexcept> // בשביל std::runtime_error
#include <sstream>
#include <vector>
#include <fstream>
#include <queue>
#include "json.hpp"
#include <map>
#include <stack>
#include <unordered_map>

using json = nlohmann::json;

class Global
{
public:
	static unsigned int win_width;
	static unsigned int win_height;
};

std::uint32_t IpToUint32_t(const std::string& ip);
bool OpenFile(std::vector<std::string>& lines, const std::string& file_name);

struct Package {

	static const std::string& Pack(const std::string& action, const std::string& data);
	static const std::map<std::string, std::string>& Unpack(const std::string& massage);
};
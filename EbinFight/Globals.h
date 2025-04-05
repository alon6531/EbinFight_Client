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
#include <map>
#include <stack>


std::uint32_t IpToUint32_t(const std::string& ip);
bool OpenFile(std::vector<std::string>& lines, const std::string& file_name);

struct Package {

	static const std::string& Pack(const std::string& action, const std::string& data);
	static const std::map<std::string, std::string>& Unpack(const std::string& massage);
};
#pragma once

#include "Globals.h"


class Handle_Controls
{
public:
	Handle_Controls(const std::string& file_path);
	

	const sf::Keyboard::Key GetControls(const std::string& control_purpose) const;

private:
	void Init(const std::string& file_path);
	sf::Keyboard::Key StringToKey(const std::string& str);

private:
	std::map<std::string, sf::Keyboard::Key> m_controls;
};


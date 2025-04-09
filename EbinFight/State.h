#pragma once
#include "Globals.h"
#include "Client.h"
#include "Handle_Controls.h"

class State
{
public:
	State(Client& client, std::stack<State*>& currentState);

	virtual void Handle_Events(const sf::Event& event, Handle_Controls& m_handle_controls, float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;

	virtual void OnExitState() = 0;
protected:
	std::stack<State*>& p_currentState;
	Client& p_client;
	bool isExitState;
	
};


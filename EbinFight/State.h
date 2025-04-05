#pragma once
#include "Globals.h"

class State
{
public:
	State(std::stack<State*>& currentState);

	virtual void Handle_Events() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;

	virtual void OnExitState() = 0;
protected:
	std::stack<State*>& m_currentState;
};


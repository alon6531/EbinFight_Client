#pragma once
#include "State.h"

class Game :
    public State
{
public:
	Game(std::stack<State*>& currentState);

	void Handle_Events() override;
	void Update(float dt) override;
	void Render(sf::RenderWindow& window) override;

	void OnExitState() override;
private:
};


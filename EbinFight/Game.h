#pragma once
#include "State.h"
#include "Object_Manager.h"


class Game :
    public State
{
public:
	Game(std::stack<State*>& currentState);

	void Handle_Events(const sf::Event& event, Handle_Controls& m_handle_controls, float dt) override;
	void Update(float dt) override;
	void Render(sf::RenderWindow& window) override;

	void OnExitState() override;

private:
	void Init();

private:
	Object_Manager m_objectManager;
	
};


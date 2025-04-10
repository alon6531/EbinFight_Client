#pragma once
#include "State.h"
#include "Handle_Object.h"
#include "Map.h"


class Game :
    public State
{
public:
	Game(Client& client, std::stack<State*>& currentState);


	void Handle_Events(const sf::Event& event, Handle_Controls& m_handle_controls, float dt) override;
	void Update(float dt) override;
	void Render(sf::RenderWindow& window) override;

	void OnExitState() override;

private:
	void Init();
	void InitPlayer();

private:
	Map* map;
	Handle_Object handleObjects;
	
};


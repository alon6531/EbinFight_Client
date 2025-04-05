#pragma once

#include "Game.h"
#include "Client.h"

class Engine
{
public:
	Engine(Client& client);
	~Engine();


	void Run();

private:
	void Init();
	void Handle_Events();
	void Update();
	void Render();
	void CloseWindow();

private:
	Client& m_client;

	sf::RenderWindow* m_window;
	unsigned int m_winWidth;
	unsigned int m_winHeight;

	sf::Clock m_clock;
	float m_dt;// delta time

	std::stack<State*> m_state;
};


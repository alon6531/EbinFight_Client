#include "Game.h"

Game::Game(std::stack<State*>& currentState) : State(currentState)
{
	std::cout << "Game:Game State Opened" << "\n";
	this->Init();
}

void Game::Init()
{
	m_objectManager = Object_Manager();

	GameObject player = GameObject("a.png", sf::Vector2f(60, 50), sf::Vector2f(50, 50));
	m_objectManager.AddObject("player", player);

}


void Game::Handle_Events(const sf::Event& event, Handle_Controls& m_handle_controls, float dt)
{
	m_objectManager.Handle_Events(event, m_handle_controls, dt);
}

void Game::Update(float dt)
{
	m_objectManager.Update(dt);
}

void Game::Render(sf::RenderWindow& window)
{
	m_objectManager.Render(window);
}

void Game::OnExitState()
{
}


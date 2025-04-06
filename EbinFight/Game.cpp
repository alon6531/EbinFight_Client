#include "Game.h"

Game::Game(Client& client, std::stack<State*>& currentState) 
	: State(client, currentState), handleObjects(client)
{
	std::cout << "Game:Game State Opened" << "\n";
	this->Init();
}

void Game::Init()
{

}


void Game::Handle_Events(const sf::Event& event, Handle_Controls& m_handle_controls, float dt)
{
	handleObjects.Handle_Events(event, m_handle_controls, dt);
}

void Game::Update(float dt)
{
	handleObjects.Update(dt);
}

void Game::Render(sf::RenderWindow& window)
{
	handleObjects.Render(window);
}

void Game::OnExitState()
{
}


#include "Game.h"

Game::Game(std::stack<State*>& currentState) : State(currentState)
{
	std::cout << "Game:Game State Opened" << "\n";
}

void Game::Handle_Events()
{
}

void Game::Update(float dt)
{
	
}

void Game::Render(sf::RenderWindow& window)
{
}

void Game::OnExitState()
{
}

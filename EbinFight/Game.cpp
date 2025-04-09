#include "Game.h"

Game::Game(Client& client, std::stack<State*>& currentState) 
	: State(client, currentState), handleObjects(client)
{
	std::cout << "Game:Game State Opened" << "\n";
	
	this->Init();
}


void Game::Init()
{
	json map_data = p_client.ReciveMapData();
	map = new Map(map_data, handleObjects);

	GameObject* player = new GameObject("..\\Assets\\a.png", sf::Vector2f(600.f, 400.f), 
		sf::Vector2f(0.3f, 0.3f));
	player->AddHitBoxComponent(sf::Vector2f(0.f, 0.f), sf::Vector2f(0, 0));
	player->AddMovementComponent(20);
	player->GetSprite()->setOrigin(player->GetSprite()->getLocalBounds().getCenter());
	handleObjects.AddObject("player", *player);
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
	

	if (map)
	{
		map->Render(window);
	}

	handleObjects.Render(window);

}

void Game::OnExitState()
{
}


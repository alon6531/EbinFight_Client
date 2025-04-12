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

	
	json player_data = p_client.ReceivePlayer();

	std::string player_name = player_data.begin().key();               // "alon"
	json player_info = player_data[player_name];              // { pos, speed, ... }

	GameObject player = GameObject::CreateObject(player_info);


	handleObjects.AddPlayer(player_name, player);
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


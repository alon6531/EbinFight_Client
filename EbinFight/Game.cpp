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

	
	// this->InitPlayer();
	json player_data = p_client.ReceivePlayer();

	std::string player_name = player_data.begin().key();               // "alon"
	json player_info = player_data[player_name]["data"];              // { pos, speed, ... }

	GameObject player = *GameObject::CreateObject(player_info);


	handleObjects.AddPlayer(player_name, player);
}

void Game::InitPlayer()
{
	json player_data = {
		{"texture", "a.png"},
		{"pos", {600.f, 400.f}},
		{"scale", {0.3f, 0.3f}},
		{"origin", "center"},
		{"hitboxComponent", {true, {0.f, 0.f}, {0, 0}}},
		{"movement_speedComponent", {true, 20}}
	};
	p_client.InitPlayer(player_data);
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


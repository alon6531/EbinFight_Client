#include "Game.h"

Game::Game(Client& client, std::stack<State*>& currentState) 
	: State(client, currentState), handleObjects(client)
{
	std::cout << "Game:Game State Opened" << "\n";
	
	this->Init();
}

Game::~Game()
{
	delete map;
}


void Game::Init()
{
	json map_data = p_client.ReciveMapData();
	map = new Map(map_data, handleObjects);

	
	json player_data = p_client.ReceivePlayer();

	std::string player_name = player_data.begin().key();               // "alon"
	json player_info = player_data[player_name];              // { pos, speed, ... }

	GameObject* player =new GameObject(player_info);
	//player->GetSprite()->setScale(sf::Vector2f(3, 3));
	//player->GetHitBoxComponent()->UpdateCompData(sf::Vector2f(0, 0), sf::Vector2f(16 * 3, 32 * 3));
	/*player->AddAnimationComponent(200);
	player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(16, 32)));
	player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(16, 0), sf::Vector2i(16, 32)));
	player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(32, 0), sf::Vector2i(16, 32)));
	player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(48, 0), sf::Vector2i(16, 32)));*/
	//player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));

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


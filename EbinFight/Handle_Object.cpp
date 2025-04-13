#include "Handle_Object.h"

Handle_Object::Handle_Object(Client& client)
	: m_client(client)
{
	m_camera = sf::Vector2f(0.f, 0.f); // fallback
	this->Init();
}

Handle_Object::~Handle_Object()
{
	for (auto it = m_objects.begin(); it != m_objects.end(); )
	{
		delete it->second;
		it = m_objects.erase(it); 
	}
}

void Handle_Object::Init()
{

}

void Handle_Object::HandleObjectsComps(const std::string& obj_name, const json& obj_data)
{
}


bool Handle_Object::FindObject(const std::string& object_name)
{
	auto it = m_objects.find(object_name);
	if (it != m_objects.end() && it->second)
	{
		return true;
	}
	return false;
}


void Handle_Object::AddObject(const std::string& obj_name, GameObject* obj)
{
	if (obj && m_objects.find(obj_name) == m_objects.end())
	{
		m_objects[obj_name] = obj;
		std::cout << "Object_Manager:Added Object: " << obj_name << "\n";
	}
	else
	{
		std::cerr << "Object_Manager:ERROR::Object already exists: " << obj_name << "\n";
	}
}

void Handle_Object::AddPlayers(const std::string& obj_name, GameObject* obj)
{
	if (obj && m_players.find(obj_name) == m_players.end())
	{
		m_players[obj_name] = obj;
		std::cout << "Object_Manager:Added Object: " << obj_name << "\n";
	}
	else
	{
		std::cerr << "Object_Manager:ERROR::Object already exists: " << obj_name << "\n";
	}
}

void Handle_Object::AddPlayer(const std::string& obj_name, GameObject* obj)
{
	if(obj)
		m_player = obj;
}

void Handle_Object::Handle_Events(const sf::Event& event, Handle_Controls& m_handle_controls, float dt)
{
	if (m_player && m_player->GetMovementComponent())
	{
		auto keyPressed = event.getIf<sf::Event::KeyPressed>();
		if (keyPressed)
		{
			if (sf::Keyboard::isKeyPressed(m_handle_controls.GetControls("Up")) &&
				sf::Keyboard::isKeyPressed(m_handle_controls.GetControls("Left")))
			{
				m_player->GetMovementComponent()->StartMoving(Left);
				m_player->GetMovementComponent()->StartMoving(Up);
				m_player->GetAnimationComponent()->Push("LeftUp", 100);
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(0, 128), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(16, 128), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(32, 128), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(48, 128), sf::Vector2i(16, 32)));
			}
			else if (sf::Keyboard::isKeyPressed(m_handle_controls.GetControls("Up")) &&
				sf::Keyboard::isKeyPressed(m_handle_controls.GetControls("Right")))
			{
				m_player->GetMovementComponent()->StartMoving(Right);
				m_player->GetMovementComponent()->StartMoving(Up);
				m_player->GetAnimationComponent()->Push("LeftUp", 100);
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(0, 96), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(16, 96), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(32, 96), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(48, 96), sf::Vector2i(16, 32)));
			}
			else if (keyPressed->code == m_handle_controls.GetControls("Left"))
			{
				m_player->GetMovementComponent()->StartMoving(Left);
				m_player->GetAnimationComponent()->Push("Left", 100);
				//m_player->GetAnimationComponent()->SetFrameTime(100);
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(0, 32), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(16, 32), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(32, 32), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(48, 32), sf::Vector2i(16, 32)));
			}
			else if (keyPressed->code == m_handle_controls.GetControls("Right"))
			{
				m_player->GetAnimationComponent()->Push("Right", 100);
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(0, 32), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(16, 32), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(32, 32), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(48, 32), sf::Vector2i(16, 32)));
				m_player->GetMovementComponent()->StartMoving(Right);
			}
			else if (keyPressed->code == m_handle_controls.GetControls("Up"))
			{
				m_player->GetMovementComponent()->StartMoving(Up);
				m_player->GetAnimationComponent()->Push("Up", 100);
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(0, 96), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(16, 96), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(32, 96), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(48, 96), sf::Vector2i(16, 32)));
			}
			else if (keyPressed->code == m_handle_controls.GetControls("Down"))
			{
				m_player->GetMovementComponent()->StartMoving(Down);
				m_player->GetAnimationComponent()->Push("Down", 100);
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(0, 32), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(16, 32), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(32, 32), sf::Vector2i(16, 32)));
				m_player->GetAnimationComponent()->AddFrame(sf::IntRect(sf::Vector2i(48, 32), sf::Vector2i(16, 32)));
			}
			
		}
		auto keyReleased = event.getIf<sf::Event::KeyReleased>();
		if (keyReleased)
		{
			if (keyReleased->code == m_handle_controls.GetControls("Up"))
			{
				m_player->GetMovementComponent()->StopMoving(Up);
			}
			else if (keyReleased->code == m_handle_controls.GetControls("Down"))
			{
				m_player->GetMovementComponent()->StopMoving(Down);
			}
			else if (keyReleased->code == m_handle_controls.GetControls("Left"))
			{
				m_player->GetMovementComponent()->StopMoving(Left);
				
			}
			else if (keyReleased->code == m_handle_controls.GetControls("Right"))
			{
				
				m_player->GetMovementComponent()->StopMoving(Right);
			}
			m_player->GetAnimationComponent()->Pop();
		}
	}
}

void Handle_Object::HandleCamera(float dt)
{
	
}

void Handle_Object::Update(float dt)
{
	std::cout << m_player->GetSprite()->getTextureRect().size.y << "\n";
	//if (this->FindObject("player"))
		//this->HandleCamera(dt);
	auto start = std::chrono::high_resolution_clock::now();
	try {
	
		json players = m_client.ReceiveAllPlayers();

		for (auto& [player_name, player_data] : players.items())
		{
			//std::cout << players.size() << "\n";

			// Always create the new GameObject


			// If player exists, delete the old one
			if (m_players.find(player_name) == m_players.end())
			{
				GameObject* new_player = new GameObject(player_data);
				this->AddPlayers(player_name, new_player);
			}
			else
			{
				m_players[player_name]->UpdateObjectData(player_data);
			}
				// Add the new player

		}
		
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
		if (e.what() == std::string("Handle_Object:Cant Update/load players")) {
		}
	}
	
	for (auto& object : m_objects)
	{
		
		object.second->Update(dt);
		
	}

	for (auto& player : m_players)
	{

		player.second->Update(dt);

	}

	if (m_player)
	{
		m_player->Update(dt);
		auto animFrames = m_player->GetAnimationComponent()->GetCurrentAnimFrames();
		
		json player_data = {
			{"pos", {m_player->GetSprite()->getPosition().x, m_player->GetSprite()->getPosition().y}},
			{"scale", {m_player->GetSprite()->getScale().x, m_player->GetSprite()->getScale().y}},
			{"AnimationComponent",
			{
			true, m_player->GetAnimationComponent()->GetCurrentframeTime(), m_player->GetAnimationComponent()->Top().getAnimName(), {
					{{animFrames[0].position.x,animFrames[0].position.y }, {animFrames[0].size.x, animFrames[0].size.y}},
					{{animFrames[1].position.x,animFrames[1].position.y }, {animFrames[1].size.x, animFrames[1].size.y}},
					{{animFrames[2].position.x,animFrames[2].position.y }, {animFrames[2].size.x, animFrames[2].size.y}},
					{{animFrames[3].position.x,animFrames[3].position.y }, {animFrames[3].size.x, animFrames[3].size.y}},
					}
			}}

			
		};
		m_client.UpdatePlayer(player_data);



		for (auto& object : m_objects)
		{
			if (m_player->GetHitBoxComponent() && object.second->GetHitBoxComponent())
			{
				
					sf::FloatRect otherRect = object.second->GetHitBoxComponent()->GetGlobalBounds();
					if (m_player->GetHitBoxComponent()->IsCollide(otherRect))
					{
						m_player->GetMovementComponent()->revertToPreviousPosition();
					}
				
			}
			
		}

		
	}
	auto end = std::chrono::high_resolution_clock::now();
	
}

void Handle_Object::Render(sf::RenderWindow& window)
{
	for (auto& object : m_objects)
	{
		
		object.second->Render(window, m_camera);
		
	}
	for (auto& player : m_players)
	{

		player.second->Render(window, m_camera);

	}

	if (m_player)
		m_player->Render(window, m_camera);

}



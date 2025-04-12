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


void Handle_Object::AddObject(const std::string& obj_name, const GameObject& obj)
{
	if (m_objects.find(obj_name) == m_objects.end())
	{
		m_objects[obj_name] = new GameObject(obj);
		std::cout << "Object_Manager:Added Object: " << obj_name << "\n";
	}
	else
	{
		std::cerr << "Object_Manager:ERROR::Object already exists: " << obj_name << "\n";
	}
}

void Handle_Object::AddPlayer(const std::string& obj_name, const GameObject& obj)
{
	m_player = new GameObject(obj);
}

void Handle_Object::Handle_Events(const sf::Event& event, Handle_Controls& m_handle_controls, float dt)
{
	if (m_player)
	{
		auto keyPressed = event.getIf<sf::Event::KeyPressed>();
		if (keyPressed)
		{
			if (keyPressed->code == m_handle_controls.GetControls("Up"))
			{
				m_player->GetMovementComponent()->StartMoving(Up);
			}
			if (keyPressed->code == m_handle_controls.GetControls("Down"))
			{
				m_player->GetMovementComponent()->StartMoving(Down);
			}
			if (keyPressed->code == m_handle_controls.GetControls("Left"))
			{
				m_player->GetMovementComponent()->StartMoving(Left);
			}
			if (keyPressed->code == m_handle_controls.GetControls("Right"))
			{
				m_player->GetMovementComponent()->StartMoving(Right);
			}

		}
		auto keyReleased = event.getIf<sf::Event::KeyReleased>();
		if (keyReleased)
		{
			if (keyReleased->code == m_handle_controls.GetControls("Up"))
			{
				m_player->GetMovementComponent()->StopMoving(Up);
			}
			if (keyReleased->code == m_handle_controls.GetControls("Down"))
			{
				m_player->GetMovementComponent()->StopMoving(Down);
			}
			if (keyReleased->code == m_handle_controls.GetControls("Left"))
			{
				m_player->GetMovementComponent()->StopMoving(Left);
			}
			if (keyReleased->code == m_handle_controls.GetControls("Right"))
			{
				m_player->GetMovementComponent()->StopMoving(Right);
			}
		}
	}
}

void Handle_Object::HandleCamera(float dt)
{
	
}

void Handle_Object::Update(float dt)
{
	
	//if (this->FindObject("player"))
		//this->HandleCamera(dt);
	try {
		json players = m_client.ReceiveAllPlayers();
	
		for (auto& [player_name, player_data] : players.items())
		{
			//std::cout << players.size() << "\n";
			std::cout << player_name << "\n";

			// Always create the new GameObject


			// If player exists, delete the old one
			if (m_objects.find(player_name) == m_objects.end())
			{
				GameObject new_player = GameObject::CreateObject(player_data);
				this->AddObject(player_name, new_player);
			}
			else
				m_objects[player_name]->UpdateObjectData(player_data);
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
	if (m_player)
	{
		m_player->Update(dt);
		json player_data = {
			{"pos", {m_player->GetSprite()->getPosition().x, m_player->GetSprite()->getPosition().y}},
			{"scale", {m_player->GetSprite()->getScale().x, m_player->GetSprite()->getScale().y}}
			
		};
		m_client.UpdatePlayer(player_data);



		/*for (auto& object : m_objects)
		{
			if (m_player->GetHitBoxComponent() && object.second->GetHitBoxComponent())
			{
				
					sf::FloatRect otherRect = object.second->GetHitBoxComponent()->GetGlobalBounds();
					if (m_player->GetHitBoxComponent()->IsCollide(otherRect))
					{
						m_player->GetMovementComponent()->revertToPreviousPosition();
					}
				
			}
			
		}*/
		
	}
}

void Handle_Object::Render(sf::RenderWindow& window)
{
	for (auto& object : m_objects)
	{
		
		object.second->Render(window, m_camera);
		
	}

	if (m_player)
		m_player->Render(window, m_camera);

}



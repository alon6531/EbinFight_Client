#include "Object_Manager.h"

Object_Manager::Object_Manager()
{
	m_camera = sf::Vector2f(0.f, 0.f); // fallback
}

void Object_Manager::AddObject(const std::string& object_name, GameObject& object)
{
	if (object.GetSprite())
	{
		
		m_objects[object_name] = new GameObject(object);

		if (object_name == "player")
		{
			HandlePlayer();
		}
	}
	else
		std::cout << "Object_Manager:Fail to create object_name" << "\n";
}

void Object_Manager::HandlePlayer()
{

	// Initialize camera centered on player position
	
	std::cout << "Object_Manager:Added Player" << "\n";
	sf::Vector2f playerPos = m_objects["player"]->GetSprite()->getPosition();
	
}

bool Object_Manager::FindObject(const std::string& object_name)
{
	auto it = m_objects.find(object_name);
	if (it != m_objects.end() && it->second)
	{
		return true;
	}
	return false;
}

void Object_Manager::Handle_Events(const sf::Event& event, Handle_Controls& m_handle_controls, float dt)
{
	auto keyEvent = event.getIf<sf::Event::KeyPressed>();
	if (keyEvent)
	{
		float speed = 5000;
		if (keyEvent->code == m_handle_controls.GetControls("MoveUp"))
			m_objects["player"]->GetSprite()->move(sf::Vector2f(0, -dt * speed));

		if (keyEvent->code == m_handle_controls.GetControls("MoveDown"))
			m_objects["player"]->GetSprite()->move(sf::Vector2f(0, dt* speed));

		if (keyEvent->code == m_handle_controls.GetControls("MoveLeft"))
			m_objects["player"]->GetSprite()->move(sf::Vector2f(-dt* speed, 0));

		if (keyEvent->code == m_handle_controls.GetControls("MoveRight"))
			m_objects["player"]->GetSprite()->move(sf::Vector2f(dt * speed, 0));


	}
}

void Object_Manager::Update(float dt)
{
	if(this->FindObject("player"))
		m_camera = m_objects["player"]->GetSprite()->getGlobalBounds().getCenter() - sf::Vector2f(Global::win_width / 2, Global::win_height / 2);
	
	for (auto& object : m_objects)
	{
		
		object.second->Update(dt);
		
	}
}

void Object_Manager::Render(sf::RenderWindow& window)
{
	for (auto& object : m_objects)
	{
		
		object.second->Render(window, m_camera);
		
	}
}



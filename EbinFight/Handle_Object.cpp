#include "Handle_Object.h"

Handle_Object::Handle_Object(Client& client)
	: m_client(client)
{
	m_camera = sf::Vector2f(0.f, 0.f); // fallback
	this->Init();
}

void Handle_Object::Init()
{

}

void Handle_Object::HandleObjectsComps(const std::string& obj_name, const json& obj_data)
{
}


void Handle_Object::HandlePlayer()
{

	// Initialize camera centered on player position
	
	std::cout << "Object_Manager:Added Player" << "\n";
	sf::Vector2f playerPos = m_objects["player"]->GetSprite()->getPosition();
	
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

void Handle_Object::Handle_Events(const sf::Event& event, Handle_Controls& m_handle_controls, float dt)
{
	auto keyPressed = event.getIf<sf::Event::KeyPressed>(); 
	if (keyPressed)
	{
		if (keyPressed->code == m_handle_controls.GetControls("Up"))
		{
			m_objects["player"]->GetMovementComponent()->Move(Up);
		}
		else if (keyPressed->code == m_handle_controls.GetControls("Down"))
		{
			m_objects["player"]->GetMovementComponent()->Move(Down);
		}
		else if (keyPressed->code == m_handle_controls.GetControls("Left"))
		{
			m_objects["player"]->GetMovementComponent()->Move(Left);
		}
		else if (keyPressed->code == m_handle_controls.GetControls("Right"))
		{
			m_objects["player"]->GetMovementComponent()->Move(Right);
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
	
	for (auto& object : m_objects)
	{
		
		object.second->Update(dt);
		
	}
	if (m_objects.find("player") != m_objects.end())
	{
		for (auto& object : m_objects)
		{
			//check if object is not player
			if (object.first == "player")
				continue;
			
			//if player collide with object he couldnt go through object
			sf::FloatRect otherRect = object.second->GetHitBoxComponent()->GetGlobalBounds();
			if (m_objects["player"]->GetHitBoxComponent()->IsCollide(otherRect))
			{
				m_objects["player"]->GetMovementComponent()->revertToPreviousPosition();
			}
			
		}
		
	}
}

void Handle_Object::Render(sf::RenderWindow& window)
{
	for (auto& object : m_objects)
	{
		
		object.second->Render(window, m_camera);
		
	}
}



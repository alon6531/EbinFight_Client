#include "Handle_Object.h"

Object_Manager::Object_Manager(Client& client) 
	: m_client(client)
{
	m_camera = sf::Vector2f(0.f, 0.f); // fallback
	this->Init();
}

void Object_Manager::Init()
{
	try {
		std::string data = m_client.ReciveAllObjects();
		if (data == "empty")
		{
			std::cout << "Object_Manager:Fail to create object-> recived data: " << data << "\n";
			return;
		}

		std::vector<std::string> parts;
		std::stringstream ss(data);
		std::string token;
		while (std::getline(ss, token, '|')) {
			parts.push_back(token);
		}

		if (!parts.empty()) {
			int partsOfObject = 7;
			for (int i = 0; i + partsOfObject < parts.size();)
			{

				std::string objectName = parts[i++];
				std::string textureFilePath = parts[i++];

				float posX = static_cast<float>(std::stoi(parts[i++]));
				float posY = static_cast<float>(std::stoi(parts[i++]));
				sf::Vector2f pos = sf::Vector2f(posX, posY);

				float scaleX = static_cast<float>(std::stoi(parts[i++]));
				float scaleY = static_cast<float>(std::stoi(parts[i++]));
				sf::Vector2f scale = sf::Vector2f(scaleX, scaleY);

				
				
				m_objects[objectName] = new GameObject(textureFilePath, pos, scale);

				if (objectName == "player")
				{
					this->HandlePlayer();
				}


				this->HandleObjectsComps(objectName, parts, i);
				
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Engine:Error parsing configuration: " << e.what() << std::endl;

	}
}

void Object_Manager::HandleObjectsComps(const std::string& obj_name, const std::vector<std::string>& parts, int& i)
{
	std::string text = parts[i++];
	
	std::vector<std::string> addHitBoxCompParts;
	std::stringstream  addHitBoxCompSS(text);
	std::string addHitBoxCompToken;

	while (std::getline(addHitBoxCompSS, addHitBoxCompToken, ',')) {
		addHitBoxCompParts.push_back(addHitBoxCompToken);
	}

	if (addHitBoxCompParts[0] == "true")
	{
		float offsetX = static_cast<int>(std::stoi(addHitBoxCompParts[1]));
		float offsetY = static_cast<int>(std::stoi(addHitBoxCompParts[2]));
		float sizeX = static_cast<int>(std::stoi(addHitBoxCompParts[3]));
		float sizeY = static_cast<int>(std::stoi(addHitBoxCompParts[4]));
		m_objects[obj_name]->AddHitBoxComponent(sf::Vector2f(offsetX, offsetY), sf::Vector2f(sizeY, sizeY));
	}
		
	
	
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

void Object_Manager::HandleCamera(float dt)
{
	float cameraSpeed = 2;
	if (m_objects["player"]->GetSprite()->getGlobalBounds().getCenter().x > Global::win_width * 0.8)
		m_camera = m_objects["player"]->GetSprite()->getGlobalBounds().getCenter();
	if (m_objects["player"]->GetSprite()->getGlobalBounds().getCenter().x < Global::win_width * 0.2)
		m_camera = m_objects["player"]->GetSprite()->getGlobalBounds().getCenter();
	if (m_objects["player"]->GetSprite()->getGlobalBounds().getCenter().y > Global::win_height * 0.8)
		m_camera = m_objects["player"]->GetSprite()->getGlobalBounds().getCenter();
	if (m_objects["player"]->GetSprite()->getGlobalBounds().getCenter().y < Global::win_height * 0.2)
		m_camera = m_objects["player"]->GetSprite()->getGlobalBounds().getCenter();
}

void Object_Manager::Update(float dt)
{
	//if (this->FindObject("player"))
		//this->HandleCamera(dt);
	
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



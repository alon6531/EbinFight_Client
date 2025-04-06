#pragma once

#include "GameObject.h"
#include "Client.h"

class Object_Manager
{
public:
	Object_Manager(Client& client);

	void Handle_Events(const sf::Event& event, Handle_Controls& m_handle_controls, float dt); 
	void Update(float dt);
	void Render(sf::RenderWindow& window);

private:
	void Init();
	void HandleObjectsComps(const std::string& obj_name, const std::vector<std::string>& parts, int& i);
	void HandlePlayer();
	void HandleCamera(float dt);
	bool FindObject(const std::string& object_name);
private:
	Client& m_client;
	std::map<std::string, GameObject*> m_objects;
	sf::Vector2f m_camera;
};


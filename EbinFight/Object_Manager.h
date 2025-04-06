#pragma once

#include "GameObject.h"

class Object_Manager
{
public:
	Object_Manager();

	void AddObject(const std::string& object_name, GameObject& object);
	void Handle_Events(const sf::Event& event, Handle_Controls& m_handle_controls, float dt);
	void Update(float dt);
	void Render(sf::RenderWindow& window);

private:
	void HandlePlayer();
	bool FindObject(const std::string& object_name);
private:
	std::map<std::string, GameObject*> m_objects;
	sf::Vector2f m_camera;
};


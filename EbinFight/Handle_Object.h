#pragma once

#include "GameObject.h"
#include "Client.h"
#include "Handle_Controls.h"

class Handle_Object
{
public:
	Handle_Object(Client& client);
	~Handle_Object();

	void AddObject(const std::string& obj_name,const GameObject& obj);
	void AddPlayer(const std::string& obj_name, const GameObject& obj);
	void Handle_Events(const sf::Event& event, Handle_Controls& m_handle_controls, float dt); 
	void Update(float dt);
	void Render(sf::RenderWindow& window);

private:
	void Init();
	void HandleObjectsComps(const std::string& obj_name, const json& obj_data);
	void HandleCamera(float dt);
	bool FindObject(const std::string& object_name);
private:
	Client& m_client;
	GameObject* m_player;
	std::map<std::string, GameObject*> m_objects;
	sf::Vector2f m_camera;
	float keyDelay = 10;
};


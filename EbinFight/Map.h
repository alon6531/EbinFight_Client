#pragma once

#include"GameObject.h"
#include "Handle_Object.h"

class Map
{
public:
	Map(const json& map_data, Handle_Object& handle_objects);
	
	//void Update(float dt);
	void Render(sf::RenderWindow& window);

private:
	void Init();
	void LoadTiles(const json& map_data);
	void LoadObjects(const json& map_data);

private:
	Handle_Object& m_handle_objects;
	sf::Texture m_tileTexture;
	std::vector<sf::Sprite> m_tiles;
	const float m_tileWidth = 32;
	const float m_tileHeight = 32;

	sf::Texture m_objectTexture;
};


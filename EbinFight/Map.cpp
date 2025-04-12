#include "Map.h"

Map::Map(const json& map_data, Handle_Object& handle_objects)
	: m_handle_objects(handle_objects)
{
	this->Init();
	this->LoadTiles(map_data);
	this->LoadObjects(map_data);
}

void Map::Init()
{
	if (!m_tileTexture.loadFromFile("..\\Assets\\Map\\tiles.png"))
		std::cout << "CANT_LOAD: " << "..\\Assets\\Map\\tiles.png" << "\n";
	if (!m_objectTexture.loadFromFile("..\\Assets\\Map\\objects.png"))
		std::cout << "CANT_LOAD: " << "..\\Assets\\Map\\objects.png" << "\n";
}

void Map::LoadTiles(const json& map_data)
{
	json tiles;

	const auto& mapEntry = map_data; // First item in the array
	if (mapEntry.contains("tiles")) {
		tiles = mapEntry["tiles"];
	}
	else {
		std::cerr << "Map: LoadMap: No tiles found in map data\n";
		return;
	}
	if (tiles.empty())
	{
		std::cerr << "Map: LoadMap: No tiles found in map data\n";
		return;
	}

	for (auto tile : tiles)
	{

		sf::Sprite tileSprite(m_tileTexture);
		if (tile["texture_pos"].is_array())
		{
			sf::Vector2i texture_pos(
				tile["texture_pos"][0].get<int>(),
				tile["texture_pos"][1].get<int>());
			sf::IntRect textureRect = sf::IntRect(texture_pos, sf::Vector2i(m_tileWidth, m_tileHeight));
			tileSprite.setTextureRect(textureRect);
		}
		if (tile["position"].is_array())
		{

			sf::Vector2f position(
				tile["position"][0].get<float>(),
				tile["position"][1].get<float>()
			);

			tileSprite.setPosition(position);
		}
		if (tile["scale"].is_array())
		{
			sf::Vector2f scale(
				tile["scale"][0].get<float>(),
				tile["scale"][1].get<float>()
			);
			tileSprite.setScale(scale);
		}
		if (tile["origin"].is_array())
		{
			sf::Vector2f origin(
				tile["origin"][0].get<float>(),
				tile["origin"][1].get<float>()
			);
			tileSprite.setOrigin(origin);
		}

		m_tiles.push_back(tileSprite);
	}

}

void Map::LoadObjects(const json& map_data)
{
	json objects;

	const auto& mapEntry = map_data; // First item in the array
	if (mapEntry.contains("objects")) {
		objects = mapEntry["objects"];
	}
	else {
		std::cerr << "Map: LoadMap: No objects found in map data\n";
		return;
	}
	if (objects.empty())
	{
		std::cerr << "Map: LoadMap: No objects found in map data\n";
		return;
	}
	
	for (auto object : objects)
	{
		std::string objectName = object["name"].get<std::string>();
		
		
		GameObject gameObject = GameObject::CreateObject(object);
	
		m_handle_objects.AddObject(objectName, gameObject);
	}
}


void Map::Render(sf::RenderWindow& window)
{
	for (auto& tile : m_tiles)
	{
		window.draw(tile);
	}
}




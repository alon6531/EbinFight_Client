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
		sf::Sprite objectSprite(m_objectTexture);
		if (object["texture_pos"].is_array())
		{
			sf::Vector2i texture_pos(
				object["texture_pos"][0].get<int>(),
				object["texture_pos"][1].get<int>());
			sf::IntRect textureRect = sf::IntRect(texture_pos, sf::Vector2i(m_tileWidth, m_tileHeight));
			objectSprite.setTextureRect(textureRect);
		}
		if (object["position"].is_array())
		{
			sf::Vector2f position(
				object["position"][0].get<float>(),
				object["position"][1].get<float>()
			);
			objectSprite.setPosition(position);
		}
		if (object["scale"].is_array())
		{
			sf::Vector2f scale(
				object["scale"][0].get<float>(),
				object["scale"][1].get<float>()
			);

			objectSprite.setScale(sf::Vector2f(scale.x, scale.y));
		}
		if (object["origin"].is_array())
		{
			sf::Vector2f origin(
				object["origin"][0].get<float>(),
				object["origin"][1].get<float>()
			);
			objectSprite.setOrigin(origin);
		}
		GameObject gameObject = GameObject(objectSprite);
		if (object["hitBoxComponent"].is_array())
		{
			bool isHitBox = object["hitBoxComponent"][0].get<bool>();
			if (isHitBox)
			{
				sf::Vector2f hitBoxPos(
					object["hitBoxComponent"][1][0].get<float>(),
					object["hitBoxComponent"][1][1].get<float>()
				);
				sf::Vector2f hitBoxSize(
					object["hitBoxComponent"][2][0].get<float>(),
					object["hitBoxComponent"][2][1].get<float>()
				);
				gameObject.AddHitBoxComponent(hitBoxPos, hitBoxSize);
			}


			//objectSprite.setSize(hitBoxSize);
		}



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




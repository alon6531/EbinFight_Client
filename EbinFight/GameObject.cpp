#include "GameObject.h"

GameObject::GameObject(const std::string& texture_filePath, const sf::Vector2f& pos, const sf::Vector2f& scale)	
{
	this->InitTexture(texture_filePath);

	sf::Vector2f newScale = sf::Vector2f(scale.x / 100, scale.y / 100);
	this->Init(pos, newScale);
}

void GameObject::InitTexture(const std::string& texture_filePath)
{
	m_spriteTexure = new sf::Texture();
	std::string path = "..\\Assets\\" + texture_filePath;
	if (!m_spriteTexure->loadFromFile(path))
	{
		std::cerr << "GameObject:ERROR::CANT_OPEN_FILE: " << texture_filePath << std::endl;
		m_spriteTexure = NULL;
	}
}

void GameObject::Init(const sf::Vector2f& pos, const sf::Vector2f& scale)
{
	if (m_spriteTexure)
		m_sprite = new sf::Sprite(*m_spriteTexure);
	else
		return;

	m_sprite->setPosition(pos);
	m_sprite->setScale(scale);

}

void GameObject::Update(float dt)
{
	if (m_sprite)
	{
	}
}

void GameObject::Render(sf::RenderWindow& window, const sf::Vector2f& camera)
{
	if (m_sprite)
	{
		// Save original position
		sf::Vector2f originalPos = m_sprite->getPosition();

		// Apply camera offset
		m_sprite->setPosition(originalPos - camera);
		std::cout << camera.x << "\n";
		// Draw sprite
		window.draw(*m_sprite);

		// Restore original position
		m_sprite->setPosition(originalPos);
	}
}

sf::Sprite* GameObject::GetSprite()
{
	if(m_sprite)
		return m_sprite;
}

#pragma once

#include "Globals.h"

class GameObject
{
public:
	GameObject(const std::string& texture_filePath, const sf::Vector2f& pos, const sf::Vector2f& scale);

	virtual void Update(float dt);

	virtual void Render(sf::RenderWindow& window, const sf::Vector2f& camera);

	 sf::Sprite* GetSprite();

private:
	void InitTexture(const std::string& texture_filePath);
	void Init(const sf::Vector2f& pos, const sf::Vector2f& scale);

protected:
	sf::Sprite* m_sprite;

private:
	sf::Texture* m_spriteTexure;

};


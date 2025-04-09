#pragma once

#include "Globals.h"
#include "HitBoxComponent.h"
#include "MovementComponent.h"

class GameObject
{
public:
	GameObject(const std::string& texture_filePath, const sf::Vector2f& pos, const sf::Vector2f& scale);
	GameObject(const sf::Sprite& sprite);
	virtual void Update(float dt);

	virtual void Render(sf::RenderWindow& window, const sf::Vector2f& camera);


	void AddHitBoxComponent(const sf::Vector2f& offset, const sf::Vector2f& size);
	void AddMovementComponent(float speed);

	




	MovementComponent* GetMovementComponent() { return m_movementComponent; }
	HitBoxComponent* GetHitBoxComponent() { return p_hitBoxComponent; }

	sf::Sprite* GetSprite() { return p_sprite; }

private:
	void InitTexture(const std::string& texture_filePath);
	void Init(const sf::Vector2f& pos, const sf::Vector2f& scale);

protected:
	sf::Sprite* p_sprite;
	MovementComponent* m_movementComponent;
	HitBoxComponent* p_hitBoxComponent;

private:
	sf::Texture* m_spriteTexure;

};


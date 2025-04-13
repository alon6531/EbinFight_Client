#pragma once

#include "Globals.h"
#include "HitBoxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include <chrono>

class GameObject
{
public:
	GameObject(const std::string& texture_filePath, const sf::Vector2f& pos, const sf::Vector2f& scale);
	GameObject(const json& object_data);
	~GameObject();
	virtual void Update(float dt);

	virtual void Render(sf::RenderWindow& window, const sf::Vector2f& camera);


	void AddHitBoxComponent(const sf::Vector2f& offset, const sf::Vector2f& size);
	void AddMovementComponent(float speed);
	void AddAnimationComponent();

	




	MovementComponent* GetMovementComponent();
	HitBoxComponent* GetHitBoxComponent();
	AnimationComponent* GetAnimationComponent();

	sf::Sprite* GetSprite() { return p_sprite; }

	void UpdateObjectData(json object_data);

private:
	void InitTexture(const std::string& texture_filePath);
	void Init(const sf::Vector2f& pos, const sf::Vector2f& scale);

protected:
	sf::Sprite* p_sprite;
	MovementComponent* p_movementComponent;
	HitBoxComponent* p_hitBoxComponent;
	AnimationComponent* p_animationComponent;

private:
	sf::Texture* m_spriteTexure;

};


#pragma once
#include "Component.h"

enum MovementDirection
{
	Up,
	Down,
	Left,
	Right
};

class MovementComponent :
    public Component
{
public:
    MovementComponent(sf::Sprite& p_sprite, float speed);

	void Update(float dt) override;

	void Render(sf::RenderWindow& window) override;

    void Move(MovementDirection dir);
    void revertToPreviousPosition();

private:

	float m_speed;
    sf::Vector2f m_position;
    sf::Vector2f m_previousPosition;
};


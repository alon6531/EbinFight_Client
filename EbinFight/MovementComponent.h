#pragma once
#include "Component.h"

enum MovementDirection
{
	Up,
	Down,
	Left,
	Right
};

#define STACK 1000

class MovementComponent :
    public Component
{
public:
    MovementComponent(sf::Sprite& p_sprite, float speed);

	void Update(float dt) override;

	void Render(sf::RenderWindow& window) override;

	void Move(MovementDirection dir, float dt);

	void StartMoving(MovementDirection dir);

	void StopMoving(MovementDirection dir);

    void revertToPreviousPosition();

	const sf::Vector2f& GetNextPosition();

	void UpdateCompData(float speed);

private:

	float m_speed;
    sf::Vector2f m_position;
    sf::Vector2f m_previousPosition;
	sf::Vector2f m_nextPosition;
	std::map<MovementDirection, bool> m_moving;

	int m_stackNum;
};


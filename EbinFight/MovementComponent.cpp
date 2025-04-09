#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& p_sprite, float speed)
	: Component(p_sprite), m_speed(speed)
{
	m_position = p_sprite.getPosition();
	m_previousPosition = m_position;
}

void MovementComponent::Update(float dt)
{
}

void MovementComponent::Render(sf::RenderWindow& window)
{
	
}

void MovementComponent::Move(MovementDirection dir)
{
	m_previousPosition = m_position;
	std::cout << "MovementComponent: " << m_previousPosition.x << "\n";
	if (dir == Up)
	{
		m_position.y -= m_speed;
	}
	else if (dir == Down)
	{
		m_position.y += m_speed;
	}
	else if (dir == Left)
	{
		m_position.x -= m_speed;
	}
	else if (dir == Right)
	{
		m_position.x += m_speed;
	}
	
	p_sprite.setPosition(m_position);
}

void MovementComponent::revertToPreviousPosition()
{
	p_sprite.setPosition(m_previousPosition);
	m_position = m_previousPosition;
}

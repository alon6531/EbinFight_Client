#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& p_sprite, float speed)
    : Component(p_sprite), m_speed(speed)
{
    m_position = p_sprite.getPosition();
    m_previousPosition = m_position;
    m_nextPosition = m_position;
    m_stackNum = 0;
    m_moving[Up] = false;
    m_moving[Down] = false;
    m_moving[Left] = false;
    m_moving[Right] = false;
}

void MovementComponent::Update(float dt)
{
     m_previousPosition = m_position;
     m_position = m_nextPosition;
    for (auto movment : m_moving)
    {
        if (movment.second)
        {
            Move(movment.first, dt);
        }
        
    }
    
}

void MovementComponent::Render(sf::RenderWindow& window)
{
    // Render logic (if needed)
    window.draw(p_sprite);
}

void MovementComponent::Move(MovementDirection dir, float dt)
{

    float movementSpeed = m_speed * dt * 0.01; // Frame-rate independent speed

    if (dir == Up)
    {
        m_nextPosition.y -= movementSpeed;
    }
    else if (dir == Down)
    {
        m_nextPosition.y += movementSpeed;
    }
    else if (dir == Left)
    {
        m_nextPosition.x -= movementSpeed;
    }
    else if (dir == Right)
    {
        m_nextPosition.x += movementSpeed;
    }

    // Apply the new position
    p_sprite.setPosition(m_nextPosition);
    if (m_nextPosition != m_previousPosition)
        m_stackNum = 0;
    
}

void MovementComponent::StartMoving(MovementDirection dir)
{
    if (dir == Up)
    {
        m_moving[Up] = true;
    }
    else if (dir == Down)
    {
        m_moving[Down] = true;
    }
    else if (dir == Left)
    {
        m_moving[Left] = true;
    }
    else if (dir == Right)
    {
        m_moving[Right] = true;
    }
}

void MovementComponent::StopMoving(MovementDirection dir)
{
    if (dir == Up)
    {
        m_moving[Up] = false;
    }
    else if (dir == Down)
    {
        m_moving[Down] = false;
    }
    else if (dir == Left)
    {
        m_moving[Left] = false;
    }
    else if (dir == Right)
    {
        m_moving[Right] = false;
    }
}

void MovementComponent::revertToPreviousPosition()
{
  
    p_sprite.setPosition(m_previousPosition);
    m_position = m_previousPosition;
    m_nextPosition = m_previousPosition;
    m_stackNum++;
    if (m_stackNum > STACK)
    {
        std::cout << "MovementComponent:STATIC_MOVING" << "\n";
        m_previousPosition = sf::Vector2f(500, 500);
        m_position = m_previousPosition;
        m_nextPosition = m_previousPosition;
        m_stackNum = 0;
      
    }

}

const sf::Vector2f& MovementComponent::GetNextPosition()
{
    return m_nextPosition;
}

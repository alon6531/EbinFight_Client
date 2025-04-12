#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, float frameTime)
    : Component(sprite),
    m_frameTime(frameTime),
    m_currentTime(0.f),
    m_currentFrame(0)
{
}

void AnimationComponent::AddFrame(const sf::IntRect& frame)
{
    m_frames.push_back(frame);
}

void AnimationComponent::SetFrameTime(float time)
{
    m_frameTime = time;
}


void AnimationComponent::Reset()
{
    m_currentTime = 0.f;
    m_currentFrame = 0;
    if (!m_frames.empty())
        p_sprite.setTextureRect(m_frames[0]);
}

void AnimationComponent::Update(float dt)
{
    if (m_frames.empty())
        return;

    // If frameTime is zero, freeze on the current frame (don't animate)
    if (m_frameTime <= 0.f)
    {
        p_sprite.setTextureRect(m_frames[m_currentFrame]);
        //p_sprite.setScale(sf::Vector2f(-p_sprite.getScale().x, -p_sprite.getScale().y));
        return;
    }

    m_currentTime += dt;

    if (m_currentTime >= m_frameTime)
    {
        m_currentTime -= m_frameTime;
        m_currentFrame = (m_currentFrame + 1) % m_frames.size();
        p_sprite.setTextureRect(m_frames[m_currentFrame]);
    }
}

void AnimationComponent::Render(sf::RenderWindow& window)
{
  
}

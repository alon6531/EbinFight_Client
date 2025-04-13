#include "AnimationSequence.h"

AnimationSequence::AnimationSequence(sf::Sprite& sprite, float frameTime)
    : m_sprite(sprite),
    m_frameTime(frameTime),
    m_currentTime(0.f),
    m_currentFrame(0)
{
}

void AnimationSequence::AddFrame(const sf::IntRect& frame)
{
    m_frames.push_back(frame);
}

void AnimationSequence::SetFrameTime(float time)
{
    m_frameTime = time;
}


void AnimationSequence::Reset()
{
    m_currentTime = 0.f;
    m_currentFrame = 0;
    if (!m_frames.empty())
        m_sprite.setTextureRect(m_frames[0]);

}

void AnimationSequence::Update(float dt)
{
    m_sprite.setOrigin(m_sprite.getLocalBounds().getCenter());
    if (m_frames.empty())
        return;

    // If frameTime is zero, freeze on the current frame (don't animate)
    if (m_frameTime <= 0.f)
    {
        m_sprite.setTextureRect(m_frames[m_currentFrame]);
        //p_sprite.setScale(sf::Vector2f(-p_sprite.getScale().x, -p_sprite.getScale().y));
        return;
    }

    m_currentTime += dt;

    if (m_currentTime >= m_frameTime)
    {
        m_currentTime -= m_frameTime;
        m_currentFrame = (m_currentFrame + 1) % m_frames.size();
        m_sprite.setTextureRect(m_frames[m_currentFrame]);
    }
}


#include "Animation.h"

Animation::Animation(sf::Sprite& sprite, const std::string& anim_name, float frameTime)
    : m_sprite(sprite),
    m_animName(anim_name),
    m_frameTime(frameTime),
    m_currentTime(0.f),
    m_currentFrame(0)
{
}

void Animation::AddFrame(const sf::IntRect& frame)
{
    m_frames.push_back(frame);
}

void Animation::SetFrameTime(float time)
{
    m_frameTime = time;
}


void Animation::Reset()
{
    m_currentTime = 0.f;
    m_currentFrame = 0;
    for (auto it = m_frames.begin(); it != m_frames.end(); )
    {
        it = m_frames.erase(it);
    }

}

void Animation::StartAgain()
{
    m_currentTime = 0.f;
    m_currentFrame = 0;
    if (!m_frames.empty())
        m_sprite.setTextureRect(m_frames[0]);
}

void Animation::Update(float dt)
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

const std::string& Animation::getAnimName() const
{
    return m_animName;
}

std::vector<sf::IntRect> Animation::Get_Frames()
{
    return m_frames;
}

float Animation::GetframeTime()
{
    return m_frameTime;
}


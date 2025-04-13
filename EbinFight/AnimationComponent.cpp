#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite)
    : Component(sprite)
{
}

AnimationComponent::~AnimationComponent()
{
    // מחיקת כל האנימציות שבמפה
    for (auto& [key, animation] : m_animations) {
        delete animation;
    }
    m_animations.clear();

    // ניקוי הסטאק (למרות שהם מצביעים על אותם אובייקטים שנמחקו כבר)
    while (!m_currentAnim.empty()) {
        m_currentAnim.pop();
    }
}

void AnimationComponent::Push(const std::string& anim_name, float frameTime)
{
    if (m_animations.find(anim_name) == m_animations.end())
    {
        m_animations[anim_name] = new Animation(p_sprite, anim_name, frameTime);
        m_currentAnim.push(m_animations[anim_name]);
    }
}


void AnimationComponent::Pop()
{
    while (GetSize() >= 2)
    {
        m_animations.erase(m_animations.find(m_currentAnim.top()->getAnimName()));
        m_currentAnim.pop();
    }
       
}

void AnimationComponent::RemoveAll()
{
    while (!m_currentAnim.empty())
    {
        m_animations.erase(m_animations.find(m_currentAnim.top()->getAnimName()));
        m_currentAnim.pop();
    }
}

void AnimationComponent::AddFrame(const sf::IntRect& frame)
{
    if (m_currentAnim.top())
        m_currentAnim.top()->AddFrame(frame);
}

void AnimationComponent::Update(float dt)
{
    if(m_currentAnim.top())
        m_currentAnim.top()->Update(dt);
}

void AnimationComponent::Render(sf::RenderWindow& window)
{
}

Animation& AnimationComponent::Top()
{
    if (m_currentAnim.top())
        return *m_currentAnim.top();
}

std::vector<sf::IntRect> AnimationComponent::GetCurrentAnimFrames()
{
    std::vector<sf::IntRect> rects;
    if (m_currentAnim.top())
    {
        return m_currentAnim.top()->Get_Frames();
    }
    return std::vector<sf::IntRect>();
}

float AnimationComponent::GetCurrentframeTime()
{
    if (m_currentAnim.top())
    {
        return m_currentAnim.top()->GetframeTime();
    }
    return 0.0;
}

int AnimationComponent::GetSize()
{
    auto anim = std::stack<Animation*>(m_currentAnim);
    int count = 0;
    while (!anim.empty())
    {
        anim.pop();
        ++count;
    }
    return count;
}


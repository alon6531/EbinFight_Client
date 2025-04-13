#pragma once
#include "Component.h"
#include "Animation.h"

class AnimationComponent : public Component
{
public:
    AnimationComponent(sf::Sprite& sprite);
    ~AnimationComponent();

    // Add a new frame to the animation
    void Push(const std::string& anim_name, float frameTime = 0.1f);
    void Pop();
    void RemoveAll();
    
    void AddFrame(const sf::IntRect& frame);

    void Update(float dt) override;
    void Render(sf::RenderWindow& window) override;

    Animation& Top();
    std::vector<sf::IntRect> GetCurrentAnimFrames();

    float GetCurrentframeTime();
private:
    int GetSize();
private:
    std::map<std::string, Animation*> m_animations;
    std::stack<Animation*> m_currentAnim;
    bool m_static;

};
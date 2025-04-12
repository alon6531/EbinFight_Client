#pragma once
#include "Component.h"


class AnimationComponent : public Component
{
public:
    AnimationComponent(sf::Sprite& sprite, float frameTime = 0.1f);

    // Add a new frame to the animation
    void AddFrame(const sf::IntRect& frame);

    // Set animation speed (seconds per frame)
    void SetFrameTime(float time);

    // Reset animation
    void Reset();

    void Update(float dt) override;
    void Render(sf::RenderWindow& window) override;

private:
    std::vector<sf::IntRect> m_frames;
    float m_frameTime;       // Time between frames
    float m_currentTime;     // Time accumulator
    std::size_t m_currentFrame;

};
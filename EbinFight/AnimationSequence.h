#pragma once

#include "Globals.h"
class AnimationSequence
{
public:
    AnimationSequence(sf::Sprite& sprite, float frameTime = 0.1f);

    // Add a new frame to the animation
    void AddFrame(const sf::IntRect& frame);

    // Set animation speed (seconds per frame)
    void SetFrameTime(float time);

    // Reset animation
    void Reset();

    void Update(float dt);

private:
    sf::Sprite& m_sprite;
    std::vector<sf::IntRect> m_frames;
    float m_frameTime;       // Time between frames
    float m_currentTime;     // Time accumulator
    std::size_t m_currentFrame;
};


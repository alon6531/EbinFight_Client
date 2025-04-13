#pragma once
#include "Globals.h"
class Animation
{
public:
    Animation(sf::Sprite& sprite, const std::string& anim_name, float frameTime = 0.1f);

    // Add a new frame to the animation
    void AddFrame(const sf::IntRect& frame);

    // Set animation speed (seconds per frame)
    void SetFrameTime(float time);

    // Reset animation
    void Reset();

    void StartAgain();

    void Update(float dt);

    const std::string& getAnimName() const;

    std::vector<sf::IntRect> Get_Frames();

    float GetframeTime();

private:
    std::string m_animName;
    sf::Sprite& m_sprite;
    std::vector<sf::IntRect> m_frames;
    float m_frameTime;       // Time between frames
    float m_currentTime;     // Time accumulator
    std::size_t m_currentFrame;
};


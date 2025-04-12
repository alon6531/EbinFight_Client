#pragma once
#include "Globals.h"
class InputField {
private:
    sf::RectangleShape m_box;
    sf::Text m_text;
    std::string m_content;
    bool m_isFocused = false;

public:
    InputField(const sf::Vector2f& position, const sf::Vector2f& size = { 200.f, 30.f });

    void handleEvent(const sf::Event& event);
    bool IsPressed(const sf::Vector2i& mousePosition);
    void render(sf::RenderWindow& window);
    void setFocus(bool focus);
    bool getFocus() const;

    std::string getContent() const;
    void setContent(const std::string& str);

    void setPosition(const sf::Vector2f& pos);
};


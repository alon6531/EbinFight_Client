#include "InputField.h"

InputField::InputField(const sf::Vector2f& position, const sf::Vector2f& size)
    : m_text(sf::Text(Global::font))
{
    m_box.setSize(size);
    m_box.setPosition(position);
    m_box.setFillColor(sf::Color(240, 240, 240));
    m_box.setOutlineColor(sf::Color::Black);
    m_box.setOutlineThickness(2.f);

    m_text.setCharacterSize(size.y / 2);
    m_text.setPosition(sf::Vector2f(position.x + 5, m_box.getGlobalBounds().getCenter().y - m_text.getCharacterSize() / 2));
    m_text.setFillColor(sf::Color::Black);
}

void InputField::handleEvent(const sf::Event& event)
{
    if (!m_isFocused) return;
   auto textEntered = event.getIf<sf::Event::TextEntered>();
if (textEntered) {
    uint32_t unicode = textEntered->unicode;
    if (unicode < 128 && std::isprint(static_cast<unsigned char>(unicode))) {
        m_content += static_cast<char>(unicode);
    }
    else if (unicode == 8 && !m_content.empty()) { // Backspace
        m_content.pop_back();
    }
    m_text.setString(m_content);
}
}

bool InputField::IsPressed(const sf::Vector2i& mousePosition) {
    // Check if mouse is over the button and if the mouse button is pressed
    if (m_box.getGlobalBounds().contains(sf::Vector2f(mousePosition))) {
        return true; // Button is pressed
    }
    return false; // Button is not pressed
}

void InputField::render(sf::RenderWindow& window)
{
    m_box.setOutlineColor(m_isFocused ? sf::Color::Blue : sf::Color::Black);
    window.draw(m_box);
    window.draw(m_text);
}

void InputField::setFocus(bool focus)
{
    m_isFocused = focus;
}

bool InputField::getFocus() const
{
    return m_isFocused;
}

std::string InputField::getContent() const
{
    return m_content;
}

void InputField::setContent(const std::string& str)
{
    m_content = str;
    m_text.setString(m_content);
}

void InputField::setPosition(const sf::Vector2f& pos)
{
    m_box.setPosition(pos);
    m_text.setPosition(sf::Vector2f(pos.x + 5, pos.y + 3));
}

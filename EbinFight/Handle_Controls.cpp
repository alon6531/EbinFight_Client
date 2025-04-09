#include "Handle_Controls.h"

Handle_Controls::Handle_Controls(const std::string& file_path)
{
    this->Init(file_path);
}

const sf::Keyboard::Key Handle_Controls::GetControls(const std::string& control_purpose) const
{
    return m_controls.at(control_purpose);
}

void Handle_Controls::Init(const std::string& file_path)
{

    std::vector<std::string> lines;
    if (OpenFile(lines, file_path))
    {

        try {
            m_controls["CloseWindow"] = this->StringToKey(lines[0]);
            m_controls["Up"] = this->StringToKey(lines[1]);
            m_controls["Down"] = this->StringToKey(lines[2]);
            m_controls["Left"] = this->StringToKey(lines[3]);
            m_controls["Right"] = this->StringToKey(lines[4]);
        }
        catch (const std::exception& e) {
            std::cerr << "Engine:Error parsing configuration: " << e.what() << std::endl;
            // You c
        }
    }
}

sf::Keyboard::Key Handle_Controls::StringToKey(const std::string& str)
{
    static const std::unordered_map<std::string, sf::Keyboard::Key> keyMap = {
    {"A", sf::Keyboard::Key::A},
    {"B", sf::Keyboard::Key::B},
    {"C", sf::Keyboard::Key::C},
    {"D", sf::Keyboard::Key::D},
    {"E", sf::Keyboard::Key::E},
    {"F", sf::Keyboard::Key::F},
    {"G", sf::Keyboard::Key::G},
    {"H", sf::Keyboard::Key::H},
    {"I", sf::Keyboard::Key::I},
    {"J", sf::Keyboard::Key::J},
    {"K", sf::Keyboard::Key::K},
    {"L", sf::Keyboard::Key::L},
    {"M", sf::Keyboard::Key::M},
    {"N", sf::Keyboard::Key::N},
    {"O", sf::Keyboard::Key::O},
    {"P", sf::Keyboard::Key::P},
    {"Q", sf::Keyboard::Key::Q},
    {"R", sf::Keyboard::Key::R},
    {"S", sf::Keyboard::Key::S},
    {"T", sf::Keyboard::Key::T},
    {"U", sf::Keyboard::Key::U},
    {"V", sf::Keyboard::Key::V},
    {"W", sf::Keyboard::Key::W},
    {"X", sf::Keyboard::Key::X},
    {"Y", sf::Keyboard::Key::Y},
    {"Z", sf::Keyboard::Key::Z},

    {"Num0", sf::Keyboard::Key::Num0},
    {"Num1", sf::Keyboard::Key::Num1},
    {"Num2", sf::Keyboard::Key::Num2},
    {"Num3", sf::Keyboard::Key::Num3},
    {"Num4", sf::Keyboard::Key::Num4},
    {"Num5", sf::Keyboard::Key::Num5},
    {"Num6", sf::Keyboard::Key::Num6},
    {"Num7", sf::Keyboard::Key::Num7},
    {"Num8", sf::Keyboard::Key::Num8},
    {"Num9", sf::Keyboard::Key::Num9},

    {"Escape", sf::Keyboard::Key::Escape},
    {"LControl", sf::Keyboard::Key::LControl},
    {"LShift", sf::Keyboard::Key::LShift},
    {"LAlt", sf::Keyboard::Key::LAlt},
    {"LSystem", sf::Keyboard::Key::LSystem},
    {"RControl", sf::Keyboard::Key::RControl},
    {"RShift", sf::Keyboard::Key::RShift},
    {"RAlt", sf::Keyboard::Key::RAlt},
    {"RSystem", sf::Keyboard::Key::RSystem},
    {"Menu", sf::Keyboard::Key::Menu},

    {"LBracket", sf::Keyboard::Key::LBracket},
    {"RBracket", sf::Keyboard::Key::RBracket},
    {"Semicolon", sf::Keyboard::Key::Semicolon},
    {"Comma", sf::Keyboard::Key::Comma},
    {"Period", sf::Keyboard::Key::Period},
    {"Slash", sf::Keyboard::Key::Slash},
    {"Backslash", sf::Keyboard::Key::Backslash},
    {"Equal", sf::Keyboard::Key::Equal},
    {"Hyphen", sf::Keyboard::Key::Hyphen},
    {"Space", sf::Keyboard::Key::Space},
    {"Enter", sf::Keyboard::Key::Enter},
    {"Backspace", sf::Keyboard::Key::Backspace},
    {"Tab", sf::Keyboard::Key::Tab},
    {"PageUp", sf::Keyboard::Key::PageUp},
    {"PageDown", sf::Keyboard::Key::PageDown},
    {"End", sf::Keyboard::Key::End},
    {"Home", sf::Keyboard::Key::Home},
    {"Insert", sf::Keyboard::Key::Insert},
    {"Delete", sf::Keyboard::Key::Delete},

    {"Add", sf::Keyboard::Key::Add},
    {"Subtract", sf::Keyboard::Key::Subtract},
    {"Multiply", sf::Keyboard::Key::Multiply},
    {"Divide", sf::Keyboard::Key::Divide},

    {"Left", sf::Keyboard::Key::Left},
    {"Right", sf::Keyboard::Key::Right},
    {"Up", sf::Keyboard::Key::Up},
    {"Down", sf::Keyboard::Key::Down},

    {"Numpad0", sf::Keyboard::Key::Numpad0},
    {"Numpad1", sf::Keyboard::Key::Numpad1},
    {"Numpad2", sf::Keyboard::Key::Numpad2},
    {"Numpad3", sf::Keyboard::Key::Numpad3},
    {"Numpad4", sf::Keyboard::Key::Numpad4},
    {"Numpad5", sf::Keyboard::Key::Numpad5},
    {"Numpad6", sf::Keyboard::Key::Numpad6},
    {"Numpad7", sf::Keyboard::Key::Numpad7},
    {"Numpad8", sf::Keyboard::Key::Numpad8},
    {"Numpad9", sf::Keyboard::Key::Numpad9},

    {"F1", sf::Keyboard::Key::F1}, {"F2", sf::Keyboard::Key::F2},
    {"F3", sf::Keyboard::Key::F3}, {"F4", sf::Keyboard::Key::F4},
    {"F5", sf::Keyboard::Key::F5}, {"F6", sf::Keyboard::Key::F6},
    {"F7", sf::Keyboard::Key::F7}, {"F8", sf::Keyboard::Key::F8},
    {"F9", sf::Keyboard::Key::F9}, {"F10", sf::Keyboard::Key::F10},
    {"F11", sf::Keyboard::Key::F11}, {"F12", sf::Keyboard::Key::F12},
    {"F13", sf::Keyboard::Key::F13}, {"F14", sf::Keyboard::Key::F14},
    {"F15", sf::Keyboard::Key::F15},

    {"Pause", sf::Keyboard::Key::Pause}
    };

    // בדיקה אם זו מחרוזת מספרית
    if (std::all_of(str.begin(), str.end(), ::isdigit))
    {
        int keycode = std::stoi(str);
        if (keycode >= 0 && keycode < sf::Keyboard::KeyCount)
            return static_cast<sf::Keyboard::Key>(keycode);
    }

    auto it = keyMap.find(str);
    if (it != keyMap.end())
        return it->second;

    throw std::invalid_argument("Unknown key: " + str);
}

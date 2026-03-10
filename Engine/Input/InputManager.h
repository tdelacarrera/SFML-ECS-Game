#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class InputManager
{
private:

    std::unordered_map<std::string, sf::Keyboard::Key> bindings;
    std::unordered_map<std::string, bool> current;
    std::unordered_map<std::string, bool> previous;

public:

    void bind(const std::string& action, sf::Keyboard::Key key);
    void nextFrame();
    void update();
    bool pressed(const std::string& action) const;
    bool justPressed(const std::string& action) const;
    bool justReleased(const std::string& action) const;
};
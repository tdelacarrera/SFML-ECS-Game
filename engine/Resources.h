#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

struct WindowResource
{
    sf::RenderWindow window;
};

struct TimeResource
{
    float deltaTime = 0;
};

struct EventResource
{
    std::vector<sf::Event> events;
};

struct GuiResource
{
    tgui::SFML_GRAPHICS::Gui gui;
};

enum class InputAction
{
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    Shoot,
    OpenMenu
};

struct InputBindings
{
    std::unordered_map<InputAction, sf::Keyboard::Key> bindings;

    void bind(InputAction action, sf::Keyboard::Key key)
    {
        bindings[action] = key;
    }

    sf::Keyboard::Key get(InputAction action)
    {
        return bindings[action];
    }
};

struct InputState
{
    std::unordered_map<InputAction, bool> pressed;

    bool isPressed(InputAction action) const
    {
        auto it = pressed.find(action);
        if(it == pressed.end()) return false;
        return it->second;
    }

    void set(InputAction action, bool value)
    {
        pressed[action] = value;
    }
};
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

struct InputBindings
{
    std::unordered_map<std::string, sf::Keyboard::Key> bindings;

    void bind(const std::string& action, sf::Keyboard::Key key)
    {
        bindings[action] = key;
    }
};

struct InputState
{
    std::unordered_map<std::string, bool> current;
    std::unordered_map<std::string, bool> previous;

    void nextFrame()
    {
        previous = current;
    }

    void set(const std::string& action, bool value)
    {
        current[action] = value;
    }

    bool pressed(const std::string& action) const
    {
        auto it = current.find(action);
        return it != current.end() && it->second;
    }

    bool justPressed(const std::string& action) const
    {
        bool c = current.contains(action) ? current.at(action) : false;
        bool p = previous.contains(action) ? previous.at(action) : false;
        return c && !p;
    }

    bool justReleased(const std::string& action) const
    {
        bool c = current.contains(action) ? current.at(action) : false;
        bool p = previous.contains(action) ? previous.at(action) : false;
        return !c && p;
    }
};
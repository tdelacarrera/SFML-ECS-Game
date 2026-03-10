#pragma once

#include "InputManager.h"



std::unordered_map<std::string, sf::Keyboard::Key> bindings;
std::unordered_map<std::string, bool> current;
std::unordered_map<std::string, bool> previous;



void InputManager::bind(const std::string& action, sf::Keyboard::Key key)
{
    bindings[action] = key;
}

void InputManager::nextFrame()
{
    previous = current;
}

void InputManager::update()
{
    for (auto& [action, key] : bindings)
    {
        current[action] = sf::Keyboard::isKeyPressed(key);
    }
}

bool InputManager::pressed(const std::string& action) const
{
    auto it = current.find(action);
    return it != current.end() &&
    it->second;
}

bool InputManager::justPressed(const std::string& action) const
{
    bool c = current.contains(action) ? current.at(action) : false;
    bool p = previous.contains(action) ? previous.at(action) : false;
    return c && !p;
}

bool InputManager::justReleased(const std::string& action) const
{
    bool c = current.contains(action) ? current.at(action) : false;
    bool p = previous.contains(action) ? previous.at(action) : false;
    return !c && p;
}

#pragma once

#include "MouseManager.h"


void MouseManager::setPosition(sf::Vector2i pos)
{
    position_ = pos;
}

sf::Vector2i MouseManager::getPosition() const
{
    return position_;
}

void MouseManager::setButton(sf::Mouse::Button button, bool pressed)
{
    buttons_[button] = pressed;
}

bool MouseManager::isPressed(sf::Mouse::Button button) const
{
    auto it = buttons_.find(button);
    if(it == buttons_.end()) return false;
        return it->second;
}

void MouseManager::setWheel(float delta)
{
    wheelDelta_ = delta;
}

float MouseManager::getWheel() const
{
    return wheelDelta_;
}

void MouseManager::clearFrame()
{
    wheelDelta_ = 0.f;
}

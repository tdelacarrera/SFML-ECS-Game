#pragma once

#include "MouseManager.h"

// position
void MouseManager::setPosition(sf::Vector2i pos)
{
    position_ = pos;
}

sf::Vector2i MouseManager::getPosition() const
{
    return position_;
}

// buttons
void MouseManager::setButton(sf::Mouse::Button button, bool pressed)
{
    currentButtons_[button] = pressed;
}

bool MouseManager::isPressed(sf::Mouse::Button button) const
{
    auto it = currentButtons_.find(button);
    return it != currentButtons_.end() ? it->second : false;
}

bool MouseManager::isJustPressed(sf::Mouse::Button button) const
{
    bool current = false;
    bool previous = false;

    auto itC = currentButtons_.find(button);
    if (itC != currentButtons_.end())
        current = itC->second;

    auto itP = previousButtons_.find(button);
    if (itP != previousButtons_.end())
        previous = itP->second;

    return current && !previous;
}

bool MouseManager::isJustReleased(sf::Mouse::Button button) const
{
    bool current = isPressed(button);
    bool previous = previousButtons_.count(button) ? previousButtons_.at(button) : false;

    return !current && previous;
}

// wheel
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


//selection
void MouseManager::startSelection(sf::Vector2f pos)
{
    isSelecting_ = true;
    start_ = pos;
    end_ = pos;
}

void MouseManager::updateSelection(sf::Vector2f pos)
{
    end_ = pos;
}

void MouseManager::endSelection()
{
    isSelecting_ = false;
}

bool MouseManager::selecting() const
{
    return isSelecting_;
}

sf::Vector2f MouseManager::getStart() const
{
    return start_;
}

sf::Vector2f MouseManager::getEnd() const
{
    return end_;
}

//update
void MouseManager::update()
{
    previousButtons_ = currentButtons_;
}
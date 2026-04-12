#include "MouseManager.hpp"

void MouseManager::processEvent(const sf::Event &event)
{
    if (const auto *moved = event.getIf<sf::Event::MouseMoved>())
    {
        position_ = moved->position;
    }

    if (const auto *pressed = event.getIf<sf::Event::MouseButtonPressed>())
    {
        pressedThisFrame_.insert(pressed->button);
    }

    if (const auto *released = event.getIf<sf::Event::MouseButtonReleased>())
    {
        releasedThisFrame_.insert(released->button);
    }

    if (const auto *wheel = event.getIf<sf::Event::MouseWheelScrolled>())
    {
        scroll_ += wheel->delta;
    }
}

bool MouseManager::isPressed(sf::Mouse::Button button) const
{
    return sf::Mouse::isButtonPressed(button);
}

bool MouseManager::isJustPressed(sf::Mouse::Button button) const
{
    return pressedThisFrame_.contains(button);
}

bool MouseManager::isJustReleased(sf::Mouse::Button button) const
{
    return releasedThisFrame_.contains(button);
}

sf::Vector2i MouseManager::getPosition() const
{
    return position_;
}

sf::Vector2f MouseManager::getPositionF() const
{
    return sf::Vector2f(position_);
}

float MouseManager::getScroll() const
{
    return scroll_;
}

void MouseManager::endFrame()
{
    pressedThisFrame_.clear();
    releasedThisFrame_.clear();
    scroll_ = 0.f;
}

void MouseManager::startSelection(sf::Vector2f pos)
{
    selecting_ = true;
    start_ = pos;
    end_ = pos;
}

void MouseManager::updateSelection(sf::Vector2f pos)
{
    if (selecting_)
        end_ = pos;
}

void MouseManager::endSelection()
{
    selecting_ = false;
}

bool MouseManager::isSelecting() const
{
    return selecting_;
}

sf::Vector2f MouseManager::getSelectionStart() const
{
    return start_;
}

sf::Vector2f MouseManager::getSelectionEnd() const
{
    return end_;
}
#pragma once

#include <SFML/Window.hpp>
#include <unordered_map>

class MouseManager
{
public:

    void setPosition(sf::Vector2i pos);
    sf::Vector2i getPosition() const;

    void setButton(sf::Mouse::Button button, bool pressed);
    bool isPressed(sf::Mouse::Button button) const;

    void setWheel(float delta);
    float getWheel() const;

    void clearFrame();

    // selection
    void startSelection(sf::Vector2f pos);
    void updateSelection(sf::Vector2f pos);
    void endSelection();

    bool selecting() const;

    sf::Vector2f getStart() const;
    sf::Vector2f getEnd() const;

private:

    sf::Vector2i position_;
    std::unordered_map<sf::Mouse::Button, bool> buttons_;
    float wheelDelta_ = 0.f;

    bool isSelecting_ = false;
    sf::Vector2f start_;
    sf::Vector2f end_;
};
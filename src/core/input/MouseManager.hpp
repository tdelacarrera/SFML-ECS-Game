#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_set>

class MouseManager
{
public:
    void processEvent(const sf::Event &event);
    void endFrame();

    // position
    sf::Vector2i getPosition() const;
    sf::Vector2f getPositionF() const;

    // buttons
    bool isPressed(sf::Mouse::Button button) const;
    bool isJustPressed(sf::Mouse::Button button) const;
    bool isJustReleased(sf::Mouse::Button button) const;

    // scroll
    float getScroll() const;

    // selection
    void startSelection(sf::Vector2f pos);
    void updateSelection(sf::Vector2f pos);
    void endSelection();

    bool isSelecting() const;
    sf::Vector2f getSelectionStart() const;
    sf::Vector2f getSelectionEnd() const;

private:
    sf::Vector2i position_;
    float scroll_ = 0.f;

    std::unordered_set<sf::Mouse::Button> pressedThisFrame_;
    std::unordered_set<sf::Mouse::Button> releasedThisFrame_;

    bool selecting_ = false;
    sf::Vector2f start_;
    sf::Vector2f end_;
};
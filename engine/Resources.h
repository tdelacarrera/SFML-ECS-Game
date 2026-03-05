#pragma once

#include <SFML/Graphics.hpp>

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
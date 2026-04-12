#pragma once

#include <SFML/Graphics.hpp>

struct Position
{
    sf::Vector2f value;
};

struct Texture
{
    std::string textureId;
};

struct Velocity
{
    sf::Vector2f value;
};

struct Controllable
{
};

struct Shadow
{
    std::string textureId;
    sf::Vector2f offset = {12.f, -8.f};
    float alpha = 0.6f;
};

struct Selectable
{
};

struct Selected
{
};

struct PathFollower
{
    std::vector<sf::Vector2f> waypoints; // centros de los tiles a seguir
    size_t currentIndex = 0;
    float speed = 200.f;
    float arrivalDistance = 12.f; // distancia para considerar que se ha alcanzado el waypoint
};

struct PathDebug
{
    bool showPath = true;
    sf::Color color = sf::Color::Green;
    float thickness = 4.0f;
    std::vector<sf::Vector2f> currentPath;
};

struct MarkedForMining
{
};

struct MarkedForChopping
{
};

struct MarkedForHarvest
{
};

struct Minable
{
};

struct Choppable
{
};

struct Harvestable
{
};

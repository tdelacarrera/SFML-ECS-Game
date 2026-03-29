#pragma once

struct AnimalComponent
{
    sf::Vector2f direction;
    float speed;
    float changeDirectionTimer;
};

struct PathComponent
{
    std::vector<sf::Vector2i> path;
    int currentIndex = 0;
};


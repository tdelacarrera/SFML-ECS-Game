#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>


class PrefabFactory {

public:
    void spawnColonist(entt::registry& registry, sf::Vector2f position);
    void spawnEnemy(entt::registry& registry, sf::Vector2f position);
};
#pragma once
#include "WorldMap.hpp"
#include <SFML/System/Vector2.hpp>
#include <vector>

std::vector<sf::Vector2f> findPath(const WorldMap &world, sf::Vector2f startWorld, sf::Vector2f goalWorld);
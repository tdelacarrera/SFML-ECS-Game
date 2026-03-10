#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>
#include <entt/entt.hpp>

class WorldMap;

struct AStarNode
{
    int x;
    int y;
    float g;
    float f;
};

struct AStarCompare
{
    bool operator()(const AStarNode& a, const AStarNode& b) const
    {
        return a.f > b.f;
    }
};

class Pathfinding
{
public:
    std::vector<sf::Vector2i> findPath(WorldMap& world, sf::Vector2i start, sf::Vector2i goal);
    void setDestination(entt::registry& registry, entt::entity entity, sf::Vector2i goal);

private:
    float heuristic(int x1,int y1,int x2,int y2);
    std::vector<sf::Vector2i> reconstructPath(std::vector<int>& cameFrom, int width, int gx, int gy);
};
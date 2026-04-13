#pragma once

#include "WorldMap.hpp"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>
#include <algorithm>

using GridPos = std::pair<int, int>;

inline std::vector<sf::Vector2f> findPath(const WorldMap &world, sf::Vector2f startWorld, sf::Vector2f goalWorld)
{
    int tileSize = world.getTileSize();
    int w = world.getWidth();
    int h = world.getHeight();

    auto toGrid = [&](sf::Vector2f p) -> GridPos
    {
        return {static_cast<int>(p.x / tileSize), static_cast<int>(p.y / tileSize)};
    };

    auto fromGrid = [&](GridPos g) -> sf::Vector2f
    {
        return {(g.first + 0.5f) * tileSize, (g.second + 0.5f) * tileSize};
    };

    GridPos start = toGrid(startWorld);
    GridPos goal = toGrid(goalWorld);

    if (!world.inBounds(start.first, start.second) || !world.inBounds(goal.first, goal.second))
        return {};

    if (!world.at(start.first, start.second).walkable ||
        !world.at(goal.first, goal.second).walkable)
        return {};

    std::vector<std::vector<float>> gScore(w, std::vector<float>(h, std::numeric_limits<float>::infinity()));
    std::vector<std::vector<GridPos>> cameFrom(w, std::vector<GridPos>(h, {-1, -1}));

    struct Node
    {
        float f;
        int x, y;
        bool operator>(const Node &other) const { return f > other.f; }
    };

    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;

    gScore[start.first][start.second] = 0.0f;

    auto heuristic = [&](int x, int y)
    {
        return static_cast<float>(
            std::max(std::abs(x - goal.first), std::abs(y - goal.second)));
    };

    openSet.push({heuristic(start.first, start.second), start.first, start.second});

    const std::vector<std::pair<int, int>> directions = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    while (!openSet.empty())
    {
        Node curr = openSet.top();
        openSet.pop();

        for (const auto &d : directions)
        {
            int nx = curr.x + d.first;
            int ny = curr.y + d.second;

            if (!world.inBounds(nx, ny) || !world.at(nx, ny).walkable)
                continue;

            // Evitar corner cutting
            if (d.first != 0 && d.second != 0)
            {
                if (!world.at(curr.x + d.first, curr.y).walkable ||
                    !world.at(curr.x, curr.y + d.second).walkable)
                    continue;
            }

            float tentativeG = gScore[curr.x][curr.y] + world.at(nx, ny).cost;

            if (tentativeG < gScore[nx][ny])
            {
                cameFrom[nx][ny] = {curr.x, curr.y};
                gScore[nx][ny] = tentativeG;

                float f = tentativeG + heuristic(nx, ny);
                openSet.push({f, nx, ny});
            }
        }
    }

    if (gScore[goal.first][goal.second] == std::numeric_limits<float>::infinity())
        return {};

    // reconstrucción
    std::vector<GridPos> pathGrid;
    GridPos current = goal;

    while (true)
    {
        pathGrid.push_back(current);
        if (current == start)
            break;

        current = cameFrom[current.first][current.second];
    }

    std::reverse(pathGrid.begin(), pathGrid.end());

    // convertir TODO
    std::vector<sf::Vector2f> worldPath;
    for (auto &g : pathGrid)
    {
        worldPath.push_back(fromGrid(g));
    }

    return worldPath;
}

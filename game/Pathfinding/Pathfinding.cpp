#include "Pathfinding.h"
#include <queue>
#include <limits>
#include <cmath>
#include "../components/Components.h"
#include "../World/WorldMap.h"


// Chebyshev
float Pathfinding::heuristic(int x1,int y1,int x2,int y2)
{
    int dx = std::abs(x1-x2);
    int dy = std::abs(y1-y2);

    return std::max(dx,dy); 
}

std::vector<sf::Vector2i> Pathfinding::reconstructPath( std::vector<int>& cameFrom, int width, int gx, int gy)
{
    std::vector<sf::Vector2i> path;

    int index = gx + gy * width;

    while(index != -1)
    {
        int x = index % width;
        int y = index / width;

        path.push_back({x,y});

        index = cameFrom[index];
    }

    std::reverse(path.begin(),path.end());

    return path;
}

std::vector<sf::Vector2i> Pathfinding::findPath( WorldMap& world, sf::Vector2i start, sf::Vector2i goal)
{
    int width = world.width;
    int height = world.height;

    int size = width * height;

    std::priority_queue<AStarNode,std::vector<AStarNode>,AStarCompare> open;

    std::vector<float> gScore(size,std::numeric_limits<float>::infinity());
    std::vector<int> cameFrom(size,-1);

    auto index = [&](int x,int y)
    {
        return x + y * width;
    };

    gScore[index(start.x,start.y)] = 0;

    open.push({
        start.x,
        start.y,
        0,
        heuristic(start.x,start.y,goal.x,goal.y)
    });

    const sf::Vector2i dirs[8] =
    {
        {1,0},{-1,0},{0,1},{0,-1},
        {1,1},{1,-1},{-1,1},{-1,-1}
    };

    while(!open.empty())
    {
        auto current = open.top();
        open.pop();

        if(current.x == goal.x && current.y == goal.y)
        {
            return reconstructPath(cameFrom,width,goal.x,goal.y);
        }

        for(auto& d : dirs)
        {
            int nx = current.x + d.x;
            int ny = current.y + d.y;

            if(nx < 0 || ny < 0 || nx >= width || ny >= height)
                continue;

            auto& tile = world.get(nx,ny);

            if(!tile.walkable)
                continue;

           float moveCost = tile.cost * ((std::abs(d.x) + std::abs(d.y) == 2) ? 1.4142f : 1.0f);
        float tentative = gScore[index(current.x,current.y)] + moveCost;

            int ni = index(nx,ny);

            if(tentative < gScore[ni])
            {
                gScore[ni] = tentative;

                cameFrom[ni] = index(current.x,current.y);

                float f = tentative + heuristic(nx,ny,goal.x,goal.y);

                open.push({nx,ny,tentative,f});
            }
        }
    }

    return {};
}


void Pathfinding::setDestination(entt::registry& registry, entt::entity entity, sf::Vector2i goal)
{
    auto& world = registry.ctx().get<WorldMap>();

    auto& transform = registry.get<TransformComponent>(entity);

    int tileSize = 64;

    sf::Vector2i start(
        transform.position.x / tileSize,
        transform.position.y / tileSize
    );

    auto path = findPath(world,start,goal);

    auto& pathComp = registry.emplace_or_replace<PathComponent>(entity);

    pathComp.path = path;
    pathComp.currentIndex = 0;
}


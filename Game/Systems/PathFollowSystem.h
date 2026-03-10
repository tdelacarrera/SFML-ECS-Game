#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include "../Components/Components.h"
#include "../../Engine/Resources.h"


inline void PathFollowSystem(entt::registry& registry)
{
    int tileSize = 64;
    float speed = 120.f;

    auto& deltaTime = registry.ctx().get<TimeResource>().deltaTime;
    auto view = registry.view<TransformComponent, PathComponent>();

    for(auto entity : view)
    {
        auto& transform = view.get<TransformComponent>(entity);
        auto& path = view.get<PathComponent>(entity);

        if(path.currentIndex >= path.path.size())
            continue;

        auto tile = path.path[path.currentIndex];

        sf::Vector2f target(
            tile.x * tileSize + tileSize * 0.5f,
            tile.y * tileSize + tileSize * 0.5f
        );

        sf::Vector2f dir = target - transform.position;

        float len = std::sqrt(dir.x*dir.x + dir.y*dir.y);

        if(len < 5.f)
        {
            path.currentIndex++;
            continue;
        }

        dir /= len;

        transform.position += dir * speed * deltaTime;
    }
}
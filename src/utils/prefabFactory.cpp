// prefab.cpp
#include "prefabFactory.h"
#include "entityBuilder.h"


    void PrefabFactory::spawnColonist(entt::registry& registry, sf::Vector2f position)
    {
        EntityBuilder(registry)
            .create()
            .withSprite("colonist")
            .withTransform(position, {0 , 0}, 0)
            .withSound("walk")
            .build();
    }
    void PrefabFactory::spawnEnemy(entt::registry& registry, sf::Vector2f position)
    {
        EntityBuilder(registry)
        .create()
        .withSprite("colonist")
        .withTransform(position, {0 , 0}, 0)
        .withSound("walk")
        .build();
    }
#include "WorldEntitySpawner.hpp"
#include "ecs/entities/EntityFactory.hpp"

void WorldEntitySpawner::spawn(entt::registry &registry, const WorldMap &world)
{
    int tileSize = world.getTileSize();

    for (unsigned int y = 0; y < world.getHeight(); ++y)
    {
        for (unsigned int x = 0; x < world.getWidth(); ++x)
        {
            const Tile &tile = world.at(x, y);

            float wx = x * tileSize;
            float wy = y * tileSize;

            if (tile.terrain == 10)
            {
                if (rand() % 10 == 0)
                    EntityFactory::createTree(registry, wx, wy);
            }

            if (tile.terrain == 6)
            {
                if (rand() % 8 == 0)
                    EntityFactory::createPlant(registry, wx, wy);
            }

            if (tile.terrain == 4)
            {
                if (rand() % 6 == 0)
                    EntityFactory::createStone(registry, wx, wy);
            }
        }
    }
}
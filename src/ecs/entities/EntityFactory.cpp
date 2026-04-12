#include "EntityFactory.hpp"
#include "ecs/components/Components.hpp"

entt::entity EntityFactory::createPawn(entt::registry &registry, float x, float y)
{
    auto e = registry.create();

    registry.emplace<Position>(e, sf::Vector2f{x, y});
    registry.emplace<Texture>(e, "pawn");
    registry.emplace<Controllable>(e);
    registry.emplace<Shadow>(e, "pawn");
    registry.emplace<Selectable>(e);
    registry.emplace<PathFollower>(e);
    registry.emplace<PathDebug>(e);

    return e;
}

entt::entity EntityFactory::createTree(entt::registry &registry, float x, float y)
{
    auto e = registry.create();

    registry.emplace<Position>(e, sf::Vector2f{x, y});
    registry.emplace<Texture>(e, "tree");
    registry.emplace<Shadow>(e, "tree");
    registry.emplace<Choppable>(e);

    return e;
}

entt::entity EntityFactory::createPlant(entt::registry &registry, float x, float y)
{
    auto e = registry.create();

    registry.emplace<Position>(e, sf::Vector2f{x, y});
    registry.emplace<Texture>(e, "plant");
    registry.emplace<Shadow>(e, "plant");
    registry.emplace<Harvestable>(e);

    return e;
}

entt::entity EntityFactory::createStone(entt::registry &registry, float x, float y)
{
    auto e = registry.create();

    registry.emplace<Position>(e, sf::Vector2f{x, y});
    registry.emplace<Texture>(e, "stone");
    registry.emplace<Shadow>(e, "stone");
    registry.emplace<Minable>(e);

    return e;
}

entt::entity EntityFactory::createAnimal(entt::registry &registry, float x, float y)
{
    auto e = registry.create();

    registry.emplace<Position>(e, sf::Vector2f{x, y});
    registry.emplace<Texture>(e, "animal");
    registry.emplace<Shadow>(e, "animal");

    return e;
}
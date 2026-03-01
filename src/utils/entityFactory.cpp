#include "entityFactory.h"
#include "../components/components.h"



    void EntityFactory::createPlayer(entt::registry& registry, TextureManager& textures)
    {
        entt::entity entity = registry.create();
        registry.emplace<TransformComponent>(entity,sf::Vector2f{0.f, 0.f},  sf::Vector2f{1.f, 1.f},  0.f);
        registry.emplace<SpriteComponent>(entity, "colonist");
        registry.emplace<SoundComponent>(entity, "test");
    }
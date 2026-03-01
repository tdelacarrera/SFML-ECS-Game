#include "entityBuilder.h"
#include "../components/components.h"

    EntityBuilder::EntityBuilder(entt::registry& registry)
        : registry_(registry)
    {
        entity_ = registry_.create();
    }

    EntityBuilder& EntityBuilder::withSprite(std::string id)
    {
        registry_.emplace<SpriteComponent>(entity_, id);
        return *this;
    }
    EntityBuilder& EntityBuilder::withTransform(sf::Vector2f position, sf::Vector2f scale, float rotation)
    {
        registry_.emplace<TransformComponent>(entity_, position, scale, rotation);
        return *this;
    }
    EntityBuilder& EntityBuilder::withSound(std::string id)
    {
        registry_.emplace<SoundComponent>(entity_, id);
        return *this;
    }
    entt::entity EntityBuilder::build() { return entity_; }
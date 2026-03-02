#include "entityBuilder.h"
#include "components/components.h"

    EntityBuilder::EntityBuilder(entt::registry& registry)
        : registry_(registry)
    {
    }

    EntityBuilder& EntityBuilder::create()
    {
        entity_ = registry_.create();
        return *this;
    }

    EntityBuilder& EntityBuilder::withSprite(const std::string& id)
    {
        registry_.emplace<SpriteComponent>(entity_, id);
        return *this;
    }

    EntityBuilder& EntityBuilder::withTransform(sf::Vector2f position, sf::Vector2f scale, float rotation)
    {
        registry_.emplace<TransformComponent>(entity_, position, scale, rotation);
        return *this;
    }

    EntityBuilder& EntityBuilder::withSound(const std::string& id)
    {
        registry_.emplace<SoundComponent>(entity_, id);
        return *this;
    }
    entt::entity EntityBuilder::build() const { return entity_; }
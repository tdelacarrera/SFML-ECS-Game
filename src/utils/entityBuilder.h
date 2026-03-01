#pragma once


#include <entt/entt.hpp>
#include "textureManager.h"

class EntityBuilder {
public:
    EntityBuilder(entt::registry& registry);

    EntityBuilder& create();

    EntityBuilder& withSprite(const std::string& id);
    EntityBuilder& withTransform(sf::Vector2f position, sf::Vector2f scale, float rotation);
    EntityBuilder& withSound(const std::string& id);
    entt::entity build() const;

private:
    entt::registry& registry_;
    entt::entity entity_;
};
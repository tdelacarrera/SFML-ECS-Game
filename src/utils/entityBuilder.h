#pragma once


#include <entt/entt.hpp>
#include "textureManager.h"

class EntityBuilder {
public:
    EntityBuilder(entt::registry& registry);

    EntityBuilder& withSprite(std::string id);
    EntityBuilder& withTransform(sf::Vector2f position, sf::Vector2f scale, float rotation);
    EntityBuilder& withSound(std::string id);
    entt::entity build();

private:
    entt::registry& registry_;
    entt::entity entity_;
};
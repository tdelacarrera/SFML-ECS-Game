#pragma once


#include <entt/entt.hpp>
#include "managers/textureManager.h"

class EntityFactory {
public:
    void createPlayer(entt::registry& registry, TextureManager& textures);

private:

};
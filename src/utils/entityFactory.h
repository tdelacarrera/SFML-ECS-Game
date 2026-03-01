#pragma once


#include <entt/entt.hpp>
#include "textureManager.h"

class EntityFactory {
public:
    void createPlayer(entt::registry& registry, TextureManager& textures);

private:

};
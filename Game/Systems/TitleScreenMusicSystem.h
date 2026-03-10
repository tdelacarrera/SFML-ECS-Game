#pragma once

#include <entt/entt.hpp>
#include "../Components/Components.h"
#include "../../Engine/Resources.h"
#include "../../Engine/Audio/MusicManager.h"

inline void TitleScreenMusicSystem(entt::registry& registry)
{
    auto& music = registry.ctx().get<MusicManager>();
    music.play("music2");
}
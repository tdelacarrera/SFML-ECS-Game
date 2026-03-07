#pragma once

#include <entt/entt.hpp>
#include "../components/Components.h"
#include "../../engine/Resources.h"
#include "../../engine/MusicManager.h"
#include "../../engine/SoundManager.h"

inline void TitleScreenMusicSystem(entt::registry& registry)
{
    auto& music = registry.ctx().get<MusicManager>();
    music.play("music2", "assets/sounds/test2.,mp3");
}
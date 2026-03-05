#pragma once

#include <entt/entt.hpp>
#include "../components/Components.h"
#include "../../engine/Resources.h"
#include "../../engine/MusicManager.h"

inline void PlayBackgroundMusic(entt::registry& registry)
{
    auto& music = registry.ctx().get<MusicManager>();
    auto& sound = registry.ctx().get<SoundManager>();
    music.play("music1", "assets/sounds/test2.,mp3");
    sound.play("test2");
}
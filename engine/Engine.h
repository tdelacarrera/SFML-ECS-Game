#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "Resources.h"
#include "SystemScheduler.h"
#include "MusicManager.h"
#include "SoundManager.h"
#include "TextureManager.h"


class Engine
{
public:

    void init();
    void addSystem(Stage stage, SystemScheduler::SystemFunc sys);
    entt::registry& getRegistry();
    void run();

private:
    entt::registry registry_;
    SystemScheduler scheduler_;
};
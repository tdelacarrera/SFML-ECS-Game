#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include "Resources.h"
#include "SystemScheduler.h"


class Engine
{
public:

    void init();
    void addSystem(Stage stage, SystemScheduler::SystemFunc sys, std::vector<GameState> states);
    entt::registry& getRegistry();
    void run();

private:
    entt::registry registry_;
    SystemScheduler scheduler_;
};
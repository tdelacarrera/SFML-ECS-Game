#pragma once

#include <entt/entt.hpp>
#include "../../Engine/Resources.h"


inline void UiRenderSystem(entt::registry& registry)
{
    auto &gui = registry.ctx().get<GuiResource>().gui;
    gui.draw();
}
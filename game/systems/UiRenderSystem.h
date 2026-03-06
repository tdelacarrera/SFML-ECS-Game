#pragma once

#include <entt/entt.hpp>
#include "../../engine/Resources.h"


inline void UiRenderSystem(entt::registry& registry)
{
    auto &gui = registry.ctx().get<GuiResource>().gui;
    gui.draw();
}
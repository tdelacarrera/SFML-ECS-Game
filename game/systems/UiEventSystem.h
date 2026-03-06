#pragma once

#include <entt/entt.hpp>
#include "../../engine/Resources.h"


inline void UiEventSystem(entt::registry& registry)
{
    auto &gui = registry.ctx().get<GuiResource>().gui;
    auto &events = registry.ctx().get<EventResource>().events;

    for(auto &e : events)
        gui.handleEvent(e);
}
#pragma once

#include <entt/entt.hpp>
#include "../../engine/Resources.h"
#include "../components/Components.h"
#include <iostream>


inline void UiPauseMenuRenderSystem(entt::registry& registry)
{
    auto &gui = registry.ctx().get<GuiResource>().gui;


    auto view = registry.view<UiPauseMenuTag, UiWidgetComponent>();

    for(auto entity : view)
    {
        auto& widget = view.get<UiWidgetComponent>(entity);

        if(!widget.widget->isVisible())
        {
            widget.widget->setVisible(true);
        }
    }

}
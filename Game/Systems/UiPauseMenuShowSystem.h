#pragma once

#include <entt/entt.hpp>
#include "../../Engine/Resources.h"
#include "../Components/Components.h"
#include <iostream>


inline void UiPauseMenuShowSystem(entt::registry& registry)
{
    auto &gui = registry.ctx().get<GuiResource>().gui;
    auto& states = registry.ctx().get<GameStateStack>();
    GameState state = states.current();


    auto view = registry.view<UiPauseMenuTag, UiWidgetComponent>();

    for(auto entity : view)
    {
        auto& widget = view.get<UiWidgetComponent>(entity);

        if(state == GameState::Paused)
        {
            widget.widget->setVisible(true);
        }
        else
        {
            widget.widget->setVisible(false);
        }
    }

}
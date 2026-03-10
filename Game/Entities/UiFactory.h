#pragma once

#include <entt/entt.hpp>
#include "../Components/Components.h"

namespace EntityFactory
{

    inline entt::entity createHUD(entt::registry& registry)
    {
        auto& gui = registry.ctx().get<GuiResource>().gui;

        entt::entity hud = registry.create();

        auto label = tgui::Label::create("HUD TEXT");
        label->setPosition(10,10);
        label->setSize(200,40);

        gui.add(label);

        registry.emplace<UiWidgetComponent>(hud, label);
        registry.emplace<UiHudTag>(hud);

        return hud;
    }

    inline entt::entity createMainMenu(entt::registry& registry, const sf::Texture& texture)
    {
        auto& gui = registry.ctx().get<GuiResource>().gui;

        entt::entity menu = registry.create();

        // Panel raíz
        auto panel = tgui::Panel::create({"100%", "100%"});
        gui.add(panel);

        // Imagen de fondo
        auto background = tgui::Picture::create(texture);
        background->setSize({"100%", "100%"});
        panel->add(background);

        // Overlay oscuro
        auto overlay = tgui::Panel::create({"100%", "100%"});
        overlay->getRenderer()->setBackgroundColor(tgui::Color(0,0,0,120));
        panel->add(overlay);

        // Título
        auto title = tgui::Label::create("ECS GAME");
        title->setPosition("40%", "10%");
        title->setTextSize(40);
        overlay->add(title);

        // Botón Jugar
        auto play = tgui::Button::create("Jugar");
        play->setSize(200, 50);
        play->setPosition("40%", "40%");
        overlay->add(play);

        // Botón Opciones
        auto options = tgui::Button::create("Opciones");
        options->setSize(200, 50);
        options->setPosition("40%", "50%");
        overlay->add(options);

        // Botón Salir
        auto quit = tgui::Button::create("Salir");
        quit->setSize(200, 50);
        quit->setPosition("40%", "60%");
        overlay->add(quit);

        // Eventos
        play->onPress([&registry, panel]()
        {
            auto& states = registry.ctx().get<GameStateStack>();
            states.push(GameState::Playing);

            auto& gui = registry.ctx().get<GuiResource>().gui;
            panel->setVisible(false);

            EntityFactory::createHUD(registry);
        });

        quit->onPress([&registry]()
        {
            auto& window = registry.ctx().get<WindowResource>().window;
            window.close();
        });

        registry.emplace<UiWidgetComponent>(menu, panel);
        registry.emplace<UiMenuTag>(menu);

        return menu;
    }

    inline entt::entity createPauseMenu(entt::registry& registry)
    {
        auto& gui = registry.ctx().get<GuiResource>().gui;

        entt::entity menu = registry.create();

        // Panel raíz
        auto panel = tgui::Panel::create({"100%", "100%"});
        panel->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
        panel->setVisible(false);
        gui.add(panel);

        // Overlay oscuro
        auto overlay = tgui::Panel::create({"100%", "100%"});
        overlay->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
        panel->add(overlay);

        // Título
        auto title = tgui::Label::create("ECS GAME");
        title->setPosition("40%", "10%");
        title->setTextSize(40);
        overlay->add(title);

        // Botón Jugar
        auto play = tgui::Button::create("Jugar");
        play->setSize(200, 50);
        play->setPosition("40%", "40%");
        overlay->add(play);

        // Botón Opciones
        auto options = tgui::Button::create("Opciones");
        options->setSize(200, 50);
        options->setPosition("40%", "50%");
        overlay->add(options);

        // Botón Salir
        auto quit = tgui::Button::create("Salir");
        quit->setSize(200, 50);
        quit->setPosition("40%", "60%");
        overlay->add(quit);

        // Eventos
        play->onPress([&registry, panel]()
        {
            auto& states = registry.ctx().get<GameStateStack>();
            states.pop();
            panel->setVisible(false); 
        });

        quit->onPress([&registry, panel]()
        {
            auto& states = registry.ctx().get<GameStateStack>();
            states.pop();
            states.pop();
            panel->setVisible(false); 
            
        });

        registry.emplace<UiWidgetComponent>(menu, panel);
        registry.emplace<UiPauseMenuTag>(menu);

        return menu;
    }

}




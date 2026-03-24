#pragma once

#include <entt/entt.hpp>
#include "../Components/Components.h"

namespace EntityFactory
{


inline entt::entity createHUD(entt::registry& registry)
{
    auto& gui = registry.ctx().get<GuiResource>().gui;

    entt::entity hud = registry.create();

    //root panel
    auto root = tgui::Panel::create({"100%", "100%"});
    root->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    gui.add(root);

    // barra de recursos
    auto topBar = tgui::Panel::create({"100%", 40});
    topBar->getRenderer()->setBackgroundColor(tgui::Color(20,20,20,200));
    root->add(topBar);

    auto woodLabel = tgui::Label::create("Madera: 0");
    woodLabel->setPosition(10, 5);
    topBar->add(woodLabel);

    auto foodLabel = tgui::Label::create("Comida: 0");
    foodLabel->setPosition(150, 5);
    topBar->add(foodLabel);

    auto stoneLabel = tgui::Label::create("Piedra: 0");
    stoneLabel->setPosition(300, 5);
    topBar->add(stoneLabel);


    //barra de acciones
    auto bottomBar = tgui::Panel::create({"100%", 80});
    bottomBar->setPosition({"0%", "100% - 80"});
    bottomBar->getRenderer()->setBackgroundColor(tgui::Color(20,20,20,200));
    root->add(bottomBar);

    int x = 10;

    auto makeButton = [&](const std::string& text, ToolMode mode)
    {
        auto btn = tgui::Button::create(text);
        btn->setSize(120, 40);
        btn->setPosition(x, 20);

        btn->onPress([&registry, mode]()
        {
            auto& tool = registry.ctx().get<ToolState>();
            tool.current = mode;
        });

        bottomBar->add(btn);
        x += 130;
    };

    makeButton("Construir", ToolMode::Build);
    makeButton("Talar", ToolMode::Chop);
    makeButton("Cultivar", ToolMode::Harvest);
    makeButton("Zona", ToolMode::ZoneStorage);


    registry.emplace<UiWidgetComponent>(hud, root);
    registry.emplace<UiHudTag>(hud);

    registry.ctx().emplace<std::tuple<tgui::Label::Ptr,tgui::Label::Ptr,tgui::Label::Ptr>>(woodLabel, foodLabel, stoneLabel);
    registry.ctx().emplace<ToolState>();

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
            states.push(GameState::Menu);

            panel->setVisible(false); 
            
        });

        registry.emplace<UiWidgetComponent>(menu, panel);
        registry.emplace<UiPauseMenuTag>(menu);

        return menu;
    }

}


#pragma once

#include <entt/entt.hpp>
#include "components/Components.h"
#include "TileMap.h"

namespace Prefabs
{

    inline entt::entity createPlayer(entt::registry& registry)
    {
        entt::entity entity = registry.create();
        registry.emplace<TransformComponent>(entity,sf::Vector2f{0.f, 0.f},  sf::Vector2f{1.f, 1.f},  0.f);
        registry.emplace<SpriteComponent>(entity, "colonist");
        registry.emplace<PlayerComponent>(entity);

        return entity;
    }

    inline entt::entity createColonist(entt::registry& registry)
    {
        entt::entity entity = registry.create();
        registry.emplace<TransformComponent>(entity,sf::Vector2f{50.f, 50.f},  sf::Vector2f{1.f, 1.f},  0.f);
        registry.emplace<SpriteComponent>(entity, "colonist");

        return entity;
    }

    inline entt::entity createTileMap(entt::registry& registry, const sf::Texture& texture)
        {
            auto entity = registry.create();

            TileMapComponent tilemap;
            tilemap.texture = texture;
            tilemap.tileSize = 16;
            tilemap.width = 255;
            tilemap.height = 255;
            tilemap.vertices = sf::VertexArray(sf::PrimitiveType::Triangles);
            tilemap.tiles.resize(tilemap.width*tilemap.height);

            for (unsigned int j = 0; j < tilemap.height; ++j) {
                for (unsigned int i = 0; i < tilemap.width; ++i) {
                    if ((i + j) % 2 == 0)
                        tilemap.tiles[i + j * tilemap.width] = 0;
                    else
                        tilemap.tiles[i + j * tilemap.width] = 1;
                }
            }

            buildTileMap(tilemap);

            registry.emplace<TileMapComponent>(entity, tilemap);

            return entity;
        }

    inline entt::entity createUIButton(entt::registry& registry,const std::string& text, float x, float y)
    {
        auto& gui = registry.ctx().get<GuiResource>().gui;

        auto entity = registry.create();

        auto button = tgui::Button::create(text);
        button->setPosition(x, y);

        registry.emplace<UiWidgetComponent>(entity, button);

        gui.add(button);

        return entity;
    }

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

    inline entt::entity createMainMenu(entt::registry& registry)
    {
        auto& gui = registry.ctx().get<GuiResource>().gui;

        entt::entity menu = registry.create();

        auto panel = tgui::Panel::create({"100%","100%"});
        gui.add(panel);

        auto button = tgui::Button::create("Start");
        button->setPosition(300,250);

        panel->add(button);

        registry.emplace<UiWidgetComponent>(menu, panel);
        registry.emplace<UiMenuTag>(menu);

        return menu;
    }


}


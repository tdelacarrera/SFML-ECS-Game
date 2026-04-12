#pragma once
#include "../core/Scene.hpp"
#include <SFML/Graphics.hpp>
#include <ecs/components/Components.hpp>
#include "world/TileMap.hpp"
#include "world/Camera.hpp"
#include "world/Pathfinding.hpp"
#include "world/WorldEntitySpawner.hpp"
#include "ecs/systems/RenderSystem.hpp"
#include "ecs/systems/RenderShadows.hpp"
#include "ecs/systems/MovementSystem.hpp"
#include "ecs/systems/CameraFollowSystem.hpp"
#include "ecs/systems/SelectionRenderSystem.hpp"
#include "ecs/systems/MouseSelectionSystem.hpp"
#include "ecs/systems/SelectionRenderSystem.hpp"
#include "ecs/systems/RenderSelectionBrackets.hpp"
#include "ecs/systems/PathfindingSystem.hpp"
#include "ecs/systems/RenderPathSystem.hpp"
#include "ecs/systems/ToolApplicationSystem.hpp"
#include "ecs/systems/RenderMarked.hpp"
#include "ecs/entities/EntityFactory.hpp"
#include "core/audio/MusicManager.hpp"
#include "core/audio/SoundManager.hpp"
#include "core/input/InputManager.hpp"
#include "core/input/MouseManager.hpp"
#include <random>

class MainMenuScene;

class GameScene : public Scene
{
public:
    WorldMap world{100, 100, 32};
    TileMap tilemap;
    Camera camera;
    sf::Texture tileset;

    void onCreate() override
    {
        registry.clear();

        auto &textures = sceneManager->getGame().getTextureManager();
        textures.load("player", "assets/textures/player.png");
        textures.load("tree", "assets/textures/tree.png");
        textures.load("animal", "assets/textures/animal.png");
        textures.load("plant", "assets/textures/plant.png");
        textures.load("stone", "assets/textures/stone.png");

        auto &music = sceneManager->getGame().getMusicManager();

        music.load("game_music", "assets/music/game.mp3");
        music.play("game_music", true);

        auto &input = sceneManager->getGame().getInputManager();
        input.bind("key", sf::Keyboard::Key::Space);
        input.bind("move_up", sf::Keyboard::Key::W);
        input.bind("move_down", sf::Keyboard::Key::S);
        input.bind("move_right", sf::Keyboard::Key::D);
        input.bind("move_left", sf::Keyboard::Key::A);
        input.bind("pause", sf::Keyboard::Key::Escape);

        tileset.loadFromFile("assets/textures/tiles.png");

        std::random_device rd;
        int seed = rd();

        world.generate(seed);

        tilemap.load(tileset, world);

        WorldEntitySpawner::spawn(registry, world);

        camera.setSize({1600, 900});
        camera.setTarget({0, 0});

        EntityFactory::createPlayer(registry, 250, 300);
        createHUD();

        registry.ctx().emplace<ToolState>();
    }

    void update(float dt) override
    {
        auto &inputManager = sceneManager->getGame().getInputManager();
        auto &mouseManager = sceneManager->getGame().getMouseManager();

        if (paused)
        {
            return;
        }

        movementSystem(registry, dt, mouseManager);
        mouseSelectionSystem(registry, *window, camera, mouseManager);
        pathfindingSystem(registry, world, *window, camera, mouseManager);
        cameraFollowSystem(registry, camera);
        ChopOrderSystem(registry, *window, camera, mouseManager);
        MineOrderSystem(registry, *window, camera, mouseManager);
        HarvestOrderSystem(registry, *window, camera, mouseManager);
        CancelOrderSystem(registry, *window, camera, mouseManager);

        tilemap.update(dt);

        float scroll = mouseManager.getScroll();
        if (scroll != 0.f)
        {
            camera.addZoom(scroll);
        }

        camera.update(dt);
    }

    void render(sf::RenderWindow &window) override
    {
        auto &textureManager = sceneManager->getGame().getTextureManager();
        auto &mouseManager = sceneManager->getGame().getMouseManager();

        window.setView(camera.getView());

        window.draw(tilemap);
        renderShadows(registry, window, textureManager);
        renderSystem(registry, window, textureManager);
        renderSelectionBrackets(registry, window, world, textureManager);
        renderPathSystem(registry, window);
        selectionRenderSystem(registry, window, mouseManager);
        renderMarked(registry, window, world);
        window.setView(window.getDefaultView());

        Scene::render(window);
    }

    void handleEvent(const sf::Event &event) override
    {
        Scene::handleEvent(event);

        if (const auto *key = event.getIf<sf::Event::KeyPressed>())
        {
            if (key->code == sf::Keyboard::Key::Escape)
            {
                paused = !paused;

                if (paused)
                {
                    createPauseMenu();
                }
                else
                {
                    gui.removeAllWidgets();
                }
            }
        }
    }
    void createPauseMenu()
    {
        gui.removeAllWidgets();

        auto overlay = tgui::Panel::create({"100%", "100%"});
        overlay->getRenderer()->setBackgroundColor(tgui::Color(0, 0, 0, 150));
        gui.add(overlay);

        auto resumeBtn = tgui::Button::create("Resume");
        resumeBtn->setSize(200, 50);
        resumeBtn->setPosition({"(&.width - width)/2", "40%"});

        resumeBtn->onPress([this]()
                           {
                               paused = false;
                               gui.removeAllWidgets();
                               createHUD(); });

        overlay->add(resumeBtn);

        auto mainMenuBtn = tgui::Button::create("Main Menu");
        mainMenuBtn->setSize(200, 50);
        mainMenuBtn->setPosition({"(&.width - width)/2", "55%"});

        mainMenuBtn->onPress([this]()
                             { sceneManager->requestSceneChange<MainMenuScene>(); });

        overlay->add(mainMenuBtn);

        auto quitBtn = tgui::Button::create("Exit");
        quitBtn->setSize(200, 50);
        quitBtn->setPosition({"(&.width - width)/2", "70%"});

        quitBtn->onPress([this]()
                         { window->close(); });

        overlay->add(quitBtn);
    }

    void createHUD()
    {
        gui.removeAllWidgets();

        auto panel = tgui::Panel::create({"100%", "100%"});
        gui.add(panel);

        // Barra inferior
        auto bar = tgui::Panel::create({"100%", "80"});
        bar->setPosition({"0", "100% - 80"});
        panel->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
        panel->add(bar);

        auto makeButton = [&](const std::string &text, ToolMode mode, float x)
        {
            auto btn = tgui::Button::create(text);
            btn->setSize(120, 40);
            btn->setPosition({x, 20});

            btn->onPress([this, mode]()
                         {
                auto &tool = registry.ctx().get<ToolState>();
                tool.current = mode; });

            bar->add(btn);
        };

        makeButton("Mine", ToolMode::Mine, 20);
        makeButton("Chop", ToolMode::Chop, 160);
        makeButton("Harvest", ToolMode::Harvest, 300);
        makeButton("Cancel", ToolMode::Cancel, 440);

        createResourcePanel(panel);
    }

    void createResourcePanel(tgui::Panel::Ptr parent)
    {
        auto panel = tgui::Panel::create({200, 150});
        panel->setPosition({10, 10});

        auto label = tgui::Label::create("Resources");
        label->setPosition(10, 10);
        panel->add(label);

        auto woodText = tgui::Label::create("Wood: 0");
        woodText->setPosition(10, 40);
        panel->add(woodText);

        auto stoneText = tgui::Label::create("Stone: 0");
        stoneText->setPosition(10, 70);
        panel->add(stoneText);

        parent->add(panel);
    }
};

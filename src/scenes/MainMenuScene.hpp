#pragma once
#include "../core/Scene.hpp"
#include "GameScene.hpp"
#include "CreditsScene.hpp"
#include <TGUI/TGUI.hpp>
#include "core/audio/MusicManager.hpp"
#include "core/audio/SoundManager.hpp"
#include "core/input/InputManager.hpp"
#include "core/input/MouseManager.hpp"

class MainMenuScene : public Scene
{
public:
    void onCreate() override
    {

        auto &music = sceneManager->getGame().getMusicManager();
        music.play("menu_music");

        // root panel
        auto rootPanel = tgui::Panel::create({"100%", "100%"});
        gui.add(rootPanel);

        // Background
       // auto background = tgui::Picture::create("assets/textures/background.png");
       // background->setSize({"100%", "100%"});
       // rootPanel->add(background);

        // Overlay
        auto overlay = tgui::Panel::create({"100%", "100%"});
        overlay->getRenderer()->setBackgroundColor(tgui::Color(0, 0, 0, 140));
        rootPanel->add(overlay);

        // Title
        auto title = tgui::Label::create("ECS GAME");
        title->setTextSize(42);
        title->setPosition("(&.width - width) / 2", "10%");
        overlay->add(title);

        // Player button
        auto playButton = tgui::Button::create("Play");
        playButton->setSize(220, 55);
        playButton->setPosition("(&.width - width) / 2", "40%");
        playButton->onPress([this]()
                            { sceneManager->requestSceneChange<GameScene>(); });
        overlay->add(playButton);

        // Credits button
        auto creditsButton = tgui::Button::create("Credits");
        creditsButton->setSize(220, 55);
        creditsButton->setPosition("(&.width - width) / 2", "50%");
        creditsButton->onPress([this]()
                               { sceneManager->requestSceneChange<CreditsScene>(); });
        overlay->add(creditsButton);

        // Exit button
        auto exitButton = tgui::Button::create("Exit");
        exitButton->setSize(220, 55);
        exitButton->setPosition("(&.width - width) / 2", "60%");
        exitButton->onPress([this]()
                            {
            if (window)
                window->close(); });
        overlay->add(exitButton);
    }

    void render(sf::RenderWindow &window) override
    {
        Scene::render(window);
    }
};
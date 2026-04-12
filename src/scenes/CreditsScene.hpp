#pragma once
#include "../core/Scene.hpp"
#include "MainMenuScene.hpp"

class CreditsScene : public Scene
{
public:
    void onCreate() override
    {
        auto title = tgui::Label::create("Credits");
        title->setPosition({"(&.width - width)/2", "20%"});
        gui.add(title);

        // back button
        auto backButton = tgui::Button::create("Back");
        backButton->setSize(200, 50);
        backButton->setPosition({"(&.width - width)/2", "60%"});

        backButton->onPress([this]()
                            { sceneManager->requestSceneChange<MainMenuScene>(); });

        gui.add(backButton);
    }

    void render(sf::RenderWindow &window) override
    {
        Scene::render(window);
    }
};
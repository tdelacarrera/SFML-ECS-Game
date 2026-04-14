#pragma once
#include <SFML/Graphics.hpp>
#include "SceneManager.hpp"
#include "core/audio/MusicManager.hpp"
#include "core/audio/SoundManager.hpp"
#include "core/input/InputManager.hpp"
#include "core/input/MouseManager.hpp"
#include "core/textures/TextureManager.hpp"

class Game
{
public:
    Game()
        : window(sf::VideoMode::getDesktopMode(), "ECS Game", sf::State::Fullscreen),
          musicManager(),
          soundManager(),
          inputManager(),
          mouseManager(),
          textureManager(),
          sceneManager(*this, window)
    {
        window.setFramerateLimit(60);
        loadResources();
    }

    void loadResources()
    {
        auto &textures = getTextureManager();
        auto &music = getMusicManager();

        textures.load("pawn", "assets/textures/pawn.png");
        textures.load("tree", "assets/textures/tree.png");
        textures.load("animal", "assets/textures/animal.png");
        textures.load("plant", "assets/textures/plant.png");
        textures.load("stone", "assets/textures/stone.png");
        textures.load("tileset", "assets/textures/tiles.png");

        music.load("menu_music", "assets/music/menu.wav");
        music.load("game_music", "assets/music/game.mp3");
    }

    void run()
    {
        sf::Clock clock;

        while (window.isOpen())
        {
            float dt = clock.restart().asSeconds();

            handleEvents();
            update(dt);
            render();
        }
    }

    SceneManager &getSceneManager() { return sceneManager; }
    MusicManager &getMusicManager() { return musicManager; }
    SoundManager &getSoundManager() { return soundManager; }
    InputManager &getInputManager() { return inputManager; }
    MouseManager &getMouseManager() { return mouseManager; }
    TextureManager &getTextureManager() { return textureManager; }
    sf::RenderWindow &getWindow() { return window; }

private:
    sf::RenderWindow window;
    SceneManager sceneManager;
    MusicManager musicManager;
    SoundManager soundManager;
    InputManager inputManager;
    MouseManager mouseManager;
    TextureManager textureManager;

    void handleEvents()
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            mouseManager.processEvent(*event);

            if (sceneManager.getCurrentScene())
                sceneManager.getCurrentScene()->handleEvent(*event);
        }
    }

    void update(float dt)
    {
        inputManager.update();

        if (sceneManager.getCurrentScene())
            sceneManager.getCurrentScene()->update(dt);

        mouseManager.endFrame();

        inputManager.nextFrame();
        sceneManager.applyPendingChange();
    }

    void render()
    {
        window.clear();

        if (sceneManager.getCurrentScene())
            sceneManager.getCurrentScene()->render(window);

        window.display();
    }
};
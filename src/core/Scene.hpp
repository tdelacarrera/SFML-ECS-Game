#pragma once
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class SceneManager;

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void onCreate() {}
    virtual void onDestroy() {}

    virtual void handleEvent(const sf::Event &event)
    {
        gui.handleEvent(event);
    }

    virtual void update(float dt) {}

    virtual void render(sf::RenderWindow &window)
    {
        gui.draw();
    }

    void setSceneManager(SceneManager *manager)
    {
        sceneManager = manager;
    }

    void setWindow(sf::RenderWindow &win)
    {
        window = &win;
        gui.setTarget(win);
    }

    bool isPaused() const { return paused; }

    void setPaused(bool p) { paused = p; }

protected:
    entt::registry registry;
    tgui::SFML_GRAPHICS::Gui gui;
    sf::RenderWindow *window = nullptr;
    SceneManager *sceneManager = nullptr;
    bool paused = false;
};
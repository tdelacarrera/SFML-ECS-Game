#include "Engine.h"

void Engine::init()
{
    registry_.ctx().emplace<WindowResource>(
        sf::RenderWindow(sf::VideoMode({1600,900}), "ECS Game")
    );

    registry_.ctx().emplace<TimeResource>();
    registry_.ctx().emplace<MusicManager>(); 
    registry_.ctx().emplace<SoundManager>(); 
    registry_.ctx().emplace<TextureManager>(); 
    registry_.ctx().emplace<EventResource>(); 
    registry_.ctx().emplace<GuiResource>();
    registry_.ctx().emplace<GameStateStack>();
    registry_.ctx().emplace<InputBindings>();
    registry_.ctx().emplace<InputState>();
    registry_.ctx().emplace<WorldMap>(255,255);

    auto &gui = registry_.ctx().get<GuiResource>().gui;
    auto &window = registry_.ctx().get<WindowResource>().window;

    gui.setTarget(window);
    
}

void Engine::addSystem(Stage stage, SystemScheduler::SystemFunc sys, std::vector<GameState> states)
{
    scheduler_.add(stage, sys, states);
}

entt::registry& Engine::getRegistry()
{
    return registry_;
}

void Engine::run()
{
    auto &window = registry_.ctx().get<WindowResource>().window;
    auto &time = registry_.ctx().get<TimeResource>();
    auto &eventResource = registry_.ctx().get<EventResource>();

    sf::Clock clock;

    scheduler_.runOnce(registry_);

    while(window.isOpen())
    {
        time.deltaTime = clock.restart().asSeconds();

        eventResource.events.clear();

        while(const std::optional event = window.pollEvent())
        {
            eventResource.events.push_back(*event);

            if(event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        scheduler_.run(registry_);

        window.display();
    }
}


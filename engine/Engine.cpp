#include "Engine.h"

void Engine::init()
{
    registry_.ctx().emplace<WindowResource>(
        sf::RenderWindow(sf::VideoMode({800,600}), "ECS Game")
    );

    registry_.ctx().emplace<TimeResource>();
    registry_.ctx().emplace<MusicManager>(); 
    registry_.ctx().emplace<SoundManager>(); 
    registry_.ctx().emplace<TextureManager>(); 
    registry_.ctx().emplace<EventResource>(); 
}

void Engine::addSystem(Stage stage, SystemScheduler::SystemFunc sys)
{
    scheduler_.add(stage, sys);
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


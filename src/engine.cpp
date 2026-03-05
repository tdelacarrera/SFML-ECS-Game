#include "engine.h"
#include "mainScene.h"

#include <iostream>


Engine::Engine() 
    : window_(sf::VideoMode({static_cast<unsigned int>(config_.windowSize.x), static_cast<unsigned int>(config_.windowSize.y)}), config_.windowTitle, sf::Style::Close | sf::Style::Titlebar), context_(window_)
{
    Init();
}

Engine::~Engine() {
    Cleanup();
}

void Engine::Init() {
    window_.setFramerateLimit(60);
    //window_.setVerticalSyncEnabled(true);

    context_.sceneManager_.PushScene(std::make_unique<MainScene>(context_));
}

void Engine::Run() {
    while (running_ && window_.isOpen()) {
        float dt = clock_.restart().asSeconds();

        ProcessEvents();

        context_.input_.update();


        Update(dt);

        window_.clear(sf::Color(10, 12, 18));
        Render();
        window_.display();
    }
}

void Engine::ProcessEvents() {
    while (const auto optEvent = window_.pollEvent()) {
        const sf::Event& event = *optEvent;

        if (event.is<sf::Event::Closed>()) {
            window_.close();
            running_ = false;
            return;
        }

        context_.sceneManager_.HandleEvent(event);
    }
}

void Engine::Update(float dt) {
    context_.sceneManager_.Update(dt);
}

void Engine::Render() {
    context_.sceneManager_.Render(window_);
}

void Engine::Cleanup() {
    while (context_.sceneManager_.GetActiveScene()) {
        context_.sceneManager_.PopScene();
    }
}
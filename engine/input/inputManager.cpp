#include "inputManager.h"
#include <SFML/Window/Event.hpp>

InputManager::InputManager(sf::RenderWindow& window) : window_(window) {
    bindKey(Action::MoveUp,    sf::Keyboard::Scan::W);
    bindKey(Action::MoveUp,    sf::Keyboard::Scan::Up);
    bindKey(Action::MoveDown,  sf::Keyboard::Scan::S);
    bindKey(Action::MoveDown,  sf::Keyboard::Scan::Down);
    bindKey(Action::MoveLeft,  sf::Keyboard::Scan::A);
    bindKey(Action::MoveLeft,  sf::Keyboard::Scan::Left);
    bindKey(Action::MoveRight, sf::Keyboard::Scan::D);
    bindKey(Action::MoveRight, sf::Keyboard::Scan::Right);
}

void InputManager::update() {
    previousState_ = currentState_;
    currentState_.clear();

    processEvents();
    updateActionStates();
}

void InputManager::processEvents()
{
    while (const auto event = window_.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window_.close();
        }
    }
}

void InputManager::updateActionStates() {
    for (const auto& [action, keys] : keyBindings_) {
        bool active = false;
        for (auto key : keys) {
            if (sf::Keyboard::isKeyPressed(key)) {
                active = true;
                break;
            }
        }
        currentState_[action] = active;
    }
}

bool InputManager::isActionActive(Action action) const {
    auto it = currentState_.find(action);
    return it != currentState_.end() && it->second;
}

bool InputManager::isActionJustPressed(Action action) const {
    auto curr = currentState_.find(action);
    auto prev = previousState_.find(action);
    return (curr != currentState_.end() && curr->second) &&
           (prev == previousState_.end() || !prev->second);
}

bool InputManager::isActionJustReleased(Action action) const {
    auto curr = currentState_.find(action);
    auto prev = previousState_.find(action);
    return (curr == currentState_.end() || !curr->second) &&
           (prev != previousState_.end() && prev->second);
}


void InputManager::bindKey(Action action, sf::Keyboard::Scan key) {
    keyBindings_[action].push_back(key);
}
#pragma once
#include <SFML/Window.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

enum class Action {
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight
};

class InputManager {
public:
    explicit InputManager(sf::RenderWindow& window);

    void update();


    bool isActionActive(Action action) const;
    bool isActionJustPressed(Action action) const;
    bool isActionJustReleased(Action action) const;


    bool isKeyDown(sf::Keyboard::Scan key) const;
    sf::Vector2f getMousePosition() const;
    sf::Vector2f getMouseWorldPosition(const sf::View& view) const;


    void bindKey(Action action, sf::Keyboard::Scan key);
    void bindMouseButton(Action action, sf::Mouse::Button btn);

private:
    sf::RenderWindow& window_;


    std::unordered_map<Action, std::vector<sf::Keyboard::Scan>> keyBindings_;
    std::unordered_map<Action, std::vector<sf::Mouse::Button>> mouseBindings_;

    std::unordered_map<Action, bool> currentState_;
    std::unordered_map<Action, bool> previousState_;

    void processEvents();
    void updateActionStates();
};
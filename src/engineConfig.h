#pragma once
#include <SFML/System/Vector2.hpp>
#include <string>

struct EngineConfig{

    std::string windowTitle = "game title";
    sf::Vector2i windowSize = {1200, 800};
};


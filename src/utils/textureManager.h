#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

class TextureManager {
public:
    TextureManager() = default;
    sf::Texture& get(const std::string& path) const;
    sf::Texture& load(const std::string& key, const std::string& path);
    void clear();

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> resources_;
};
#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

class TextureCache {
public:
    TextureCache() = default;
    sf::Texture& get(const std::string& key_or_path);
    sf::Texture& load(const std::string& logicalName, const std::string& path);
    void clear();

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> cache_;
};
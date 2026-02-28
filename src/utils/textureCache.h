#pragma once

#include <SFML/Graphics/Texture.hpp>

class TextureCache {
public:
    TextureCache() = default;
    sf::Texture& Get(const std::string& key_or_path);
    sf::Texture& Load(const std::string& logicalName, const std::string& path);
    void Clear();

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> cache_;
};
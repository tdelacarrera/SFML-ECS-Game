#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

class TextureManager {
public:
    TextureManager() = default;

    sf::Texture& get(const std::string& path) const;
    sf::Texture& load(const std::string& id, const std::string& path);
    void clear();

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> resources_;

    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    TextureManager(TextureManager&&) = default;
    TextureManager& operator=(TextureManager&&) = default;


};
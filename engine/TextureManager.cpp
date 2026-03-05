#include "TextureManager.h"


sf::Texture& TextureManager::load(const std::string& id, const std::string& path)
{
    auto it = resources_.find(id);
    if (it != resources_.end()) {
        return *it->second;
    }

    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(path)) {
        throw std::runtime_error("Failed to load texture: " + path);
    }

    auto* raw = texture.get();
    resources_[id] = std::move(texture);
    return *raw;
}

sf::Texture& TextureManager::get(const std::string& id) const
{
    auto it = resources_.find(id);
    if (it == resources_.end()) {
        throw std::runtime_error("Texture not found: " + id);
    }
    return *it->second;
}


void TextureManager::clear()
{
    resources_.clear();
}
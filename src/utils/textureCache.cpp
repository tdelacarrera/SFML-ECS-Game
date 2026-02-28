#include "textureCache.h"


sf::Texture& TextureCache::get(const std::string& key_or_path) {
        auto it = cache_.find(key_or_path);
        if (it != cache_.end()) {
            return *it->second;
        }

        auto tex = std::make_unique<sf::Texture>();
        if (!tex->loadFromFile(key_or_path)) {
            throw std::runtime_error("Texture could not be loaded: " + key_or_path);
        }

        auto* raw = tex.get();
        cache_[key_or_path] = std::move(tex);
        return *raw;
}

sf::Texture& TextureCache::load(const std::string& logicalName, const std::string& path) {
        auto it = cache_.find(logicalName);
        if (it != cache_.end()) {
            return *it->second;
        }

        auto tex = std::make_unique<sf::Texture>();
        if (!tex->loadFromFile(path)) {
            throw std::runtime_error("Failed to load: " + path);
        }

        auto* raw = tex.get();
        cache_[logicalName] = std::move(tex);
        return *raw;
    }

void TextureCache::clear()
{
    cache_.clear();
}
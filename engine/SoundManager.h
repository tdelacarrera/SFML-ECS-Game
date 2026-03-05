#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class SoundManager {
public:
    SoundManager(size_t poolSize = 16);

    sf::SoundBuffer& load(const std::string& id, const std::string& path);
    sf::SoundBuffer& get(const std::string& id) const;
    void play(const std::string& id, float volume = 100.f, float pitch = 1.f);

private:
    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> resources_;
    std::vector<std::unique_ptr<sf::Sound>> pool_;
    size_t nextSoundIndex_ = 0;

    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    SoundManager(SoundManager&&) = default;
    SoundManager& operator=(SoundManager&&) = default;

};
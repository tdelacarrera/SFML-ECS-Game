#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class SoundManager {
public:
    SoundManager(size_t poolSize = 64);

    sf::SoundBuffer& loadSound(const std::string& key, const std::string& key_or_path);
    sf::SoundBuffer& getSoundBuffer(const std::string& key_or_path);
    void playSound(const std::string& key, float volume = 100.f, float pitch = 1.f);

private:
    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers_;
    std::vector<std::unique_ptr<sf::Sound>> soundPool_;
    size_t nextSoundIndex_ = 0;
};
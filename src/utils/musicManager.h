#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class MusicManager {
public:
    void loadMusic(const std::string& logicalName, const std::string& key_or_path);
    sf::Music& getMusic(const std::string& key);
    void playMusic(const std::string& key, bool loop = true, float volume = 50.f);
    void pauseMusic();
    void resumeMusic();
    void stopMusic();
    void setMusicVolume(float volume);

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> musics_;
    std::string currentMusicKey_;
};
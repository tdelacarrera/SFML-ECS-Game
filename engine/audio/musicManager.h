#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class MusicManager {
public:
    void load(const std::string& id, const std::string& path);
    sf::Music& get(const std::string& id) const;
    void play(const std::string& id, bool loop = true, float volume = 50.f);
    void pause();
    void resume();
    void stop();
    void setVolume(float volume);

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> resources_;
    std::string currentMusicId_;
};
#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

class MusicManager
{
public:
    MusicManager() = default;
    
    void load(const std::string& id, const std::string& path);
    sf::Music& get(const std::string& id) const;
    void play(const std::string& id, bool loop = true, float volume = 50.f);
    void pause();
    void resume();
    void stop();
    void setVolume(float volume);
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> resources_;
    std::string currentMusicId_;
private:
    MusicManager(const MusicManager&) = delete;
    MusicManager& operator=(const MusicManager&) = delete;

    MusicManager(MusicManager&&) = default;
    MusicManager& operator=(MusicManager&&) = default;
};
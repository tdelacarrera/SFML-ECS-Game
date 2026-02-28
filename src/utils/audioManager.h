#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class AudioManager {
public:
    AudioManager(size_t poolSize = 64);

    sf::SoundBuffer& loadSound(const std::string& key, const std::string& key_or_path);
    sf::SoundBuffer& getSoundBuffer(const std::string& key_or_path);

    void loadMusic(const std::string& logicalName, const std::string& key_or_path);
    sf::Music& getMusic(const std::string& key);

    void playSound(const std::string& key, float volume = 100.f, float pitch = 1.f);
    void playMusic(const std::string& key, bool loop = true, float volume = 50.f);
    void pauseMusic();
    void resumeMusic();
    void stopMusic();
    void setMusicVolume(float volume);

private:
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> musics_;
    std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> soundBuffers_;
    std::vector<std::unique_ptr<sf::Sound>> soundPool_;
    size_t nextSoundIndex_ = 0;
    std::string currentMusicKey_;
};

#include "musicManager.h"

void MusicManager::loadMusic(const std::string& logicalName, const std::string& path)
{
    auto it = musics_.find(logicalName);
    if (it != musics_.end()) {
        return;  // ya cargada
    }

    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(path)) {
        throw std::runtime_error("Failed to load music: " + path);
    }

    musics_[logicalName] = std::move(music);
}


sf::Music& MusicManager::getMusic(const std::string& key)
{
    auto it = musics_.find(key);
    if (it == musics_.end()) {
        throw std::runtime_error("Music key not found: " + key);
    }
    return *it->second;
}


void MusicManager::playMusic(const std::string& key, bool loop, float volume)
{
    auto it = musics_.find(key);
    if (it == musics_.end()) {
        throw std::runtime_error("Music key not found: " + key);
    }

    sf::Music& music = *it->second;

    // Sustituir por nueva si ya exista una activa
    if (currentMusicKey_ != key && !currentMusicKey_.empty()) {
        auto& prev = *musics_[currentMusicKey_];
        prev.stop();
    }

    music.setLooping(loop);
    music.setVolume(volume);
    music.play();

    currentMusicKey_ = key;
}

void MusicManager::pauseMusic()
{
    if (!currentMusicKey_.empty()) {
        musics_[currentMusicKey_]->pause();
    }
}

void MusicManager::resumeMusic()
{
    if (!currentMusicKey_.empty()) {
        musics_[currentMusicKey_]->play();
    }
}

void MusicManager::stopMusic()
{
    if (!currentMusicKey_.empty()) {
        auto& music = *musics_[currentMusicKey_];
        music.stop();
        currentMusicKey_.clear();
    }
}

void MusicManager::setMusicVolume(float volume)
{
    if (!currentMusicKey_.empty()) {
        musics_[currentMusicKey_]->setVolume(volume);
    }
}
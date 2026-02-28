
#include "audioManager.h"


AudioManager::AudioManager(size_t poolSize)
{
    soundPool_.resize(poolSize);
}
sf::SoundBuffer& AudioManager::loadSound(const std::string& logicalName, const std::string& key_or_path)
{
    auto it = soundBuffers_.find(logicalName);
    if (it != soundBuffers_.end()) {
        return *it->second;
    }

    auto buffer = std::make_unique<sf::SoundBuffer>();
    if (!buffer->loadFromFile(key_or_path)) {
        throw std::runtime_error("Failed to load: " + key_or_path);
    }

    auto* raw = buffer.get();
    soundBuffers_[logicalName] = std::move(buffer);
    return *raw;
}

sf::SoundBuffer& AudioManager::getSoundBuffer(const std::string& key_or_path)
{
    auto it = soundBuffers_.find(key_or_path);
    if (it != soundBuffers_.end()) 
    {
        return *it->second;
    }

    auto buffer = std::make_unique<sf::SoundBuffer>();
    if (!buffer->loadFromFile(key_or_path)) {
        throw std::runtime_error("Sound could not be loaded: " + key_or_path);
    }

    auto* raw = buffer.get();
    soundBuffers_[key_or_path] = std::move(buffer);
    return *raw;
}

void AudioManager::playSound(const std::string& key, float volume, float pitch)
{
    auto it = soundBuffers_.find(key);
    if (it == soundBuffers_.end()) {
        throw std::runtime_error("Sound key not found: " + key);
    }

    sf::SoundBuffer& buffer = *it->second;

    // Buscar canal libre para el sonido
    for (auto& soundPtr : soundPool_) {

        if (!soundPtr || soundPtr->getStatus() != sf::Sound::Status::Playing) {

            soundPtr = std::make_unique<sf::Sound>(buffer);
            soundPtr->setVolume(volume);
            soundPtr->setPitch(pitch);
            soundPtr->play();
            return;
        }
    }

    // Fallback round-robin
    auto& fallback = soundPool_[nextSoundIndex_];
    fallback = std::make_unique<sf::Sound>(buffer);
    fallback->setVolume(volume);
    fallback->setPitch(pitch);
    fallback->play();

    nextSoundIndex_ = (nextSoundIndex_ + 1) % soundPool_.size();
}

void AudioManager::loadMusic(const std::string& logicalName, const std::string& path)
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


sf::Music& AudioManager::getMusic(const std::string& key)
{
    auto it = musics_.find(key);
    if (it == musics_.end()) {
        throw std::runtime_error("Music key not found: " + key);
    }
    return *it->second;
}


void AudioManager::playMusic(const std::string& key, bool loop, float volume)
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

void AudioManager::pauseMusic()
{
    if (!currentMusicKey_.empty()) {
        musics_[currentMusicKey_]->pause();
    }
}

void AudioManager::resumeMusic()
{
    if (!currentMusicKey_.empty()) {
        musics_[currentMusicKey_]->play();
    }
}

void AudioManager::stopMusic()
{
    if (!currentMusicKey_.empty()) {
        auto& music = *musics_[currentMusicKey_];
        music.stop();
        currentMusicKey_.clear();
    }
}

void AudioManager::setMusicVolume(float volume)
{
    if (!currentMusicKey_.empty()) {
        musics_[currentMusicKey_]->setVolume(volume);
    }
}
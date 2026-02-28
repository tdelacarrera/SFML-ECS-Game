
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

    // Buscar canal libre
    for (auto& soundPtr : soundPool_) {

        if (!soundPtr || soundPtr->getStatus() != sf::Sound::Status::Playing) {

            // Construir directamente con buffer (SFML 3)
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
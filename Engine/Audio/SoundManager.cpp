
#include "SoundManager.h"
#include <cmath>


SoundManager::SoundManager(size_t poolSize)
{
    pool_.resize(poolSize);
}
sf::SoundBuffer& SoundManager::load(const std::string& id, const std::string& path)
{
    auto it = resources_.find(id);
    if (it != resources_.end()) {
        return *it->second;
    }

    auto buffer = std::make_unique<sf::SoundBuffer>();
    if (!buffer->loadFromFile(path)) {
        throw std::runtime_error("Failed to load sound: " + path);
    }

    auto* raw = buffer.get();
    resources_[id] = std::move(buffer);
    return *raw;
}
sf::SoundBuffer& SoundManager::get(const std::string& id) const
{
    auto it = resources_.find(id);
    if (it == resources_.end()) {
        throw std::runtime_error("Sound not found: " + id);
    }

    return *it->second;
}


void SoundManager::play(const std::string& id, float volume, float pitch, sf::Vector2f position, float maxHearingDistance)
{
    sf::Vector3f listenerPos = sf::Listener::getPosition();
    sf::Vector3f soundPos(position.x, position.y, 0.f);

    float dx = listenerPos.x - soundPos.x;
    float dy = listenerPos.y - soundPos.y;
    float dz = listenerPos.z - soundPos.z;
    float distance = std::sqrt(dx*dx + dy*dy + dz*dz);

    if(distance > maxHearingDistance)
        return; // no reproducir si el sonido esta demasiado lejos

    sf::SoundBuffer& buffer = get(id);

    for (auto& soundPtr : pool_) {
        if (!soundPtr || soundPtr->getStatus() != sf::Sound::Status::Playing) {
            soundPtr = std::make_unique<sf::Sound>(buffer);
            soundPtr->setVolume(volume);
            soundPtr->setPitch(pitch);
            soundPtr->setPosition({position.x, position.y, 0.f});
            soundPtr->setMinDistance(10.f);
            soundPtr->setAttenuation(0.5f);
            soundPtr->setRelativeToListener(false);
            soundPtr->play();
            return;
        }
    }


    auto& fallback = pool_[nextSoundIndex_];
    fallback = std::make_unique<sf::Sound>(buffer);
    fallback->setVolume(volume);
    fallback->setPitch(pitch);
    fallback->setPosition({position.x, position.y, 0.f});
    fallback->setMinDistance(50.f);
    fallback->setAttenuation(0.5f);
    fallback->setRelativeToListener(false);

    fallback->play();
    nextSoundIndex_ = (nextSoundIndex_ + 1) % pool_.size();
}


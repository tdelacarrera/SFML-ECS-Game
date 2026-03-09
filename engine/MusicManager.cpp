
#include "MusicManager.h"

void MusicManager::load(const std::string& id, const std::string& path)
{
    if (resources_.contains(id)) {
        return;
    }

    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(path)) {
        throw std::runtime_error("Failed to load music: " + path);
    }

    resources_[id] = std::move(music);
}


sf::Music& MusicManager::get(const std::string& id) const
{
    auto it = resources_.find(id);
    if (it == resources_.end()) {
        throw std::runtime_error("Music not found: " + id);
    }

    return *it->second;
}

void MusicManager::play(const std::string& id, bool loop, float volume)
{
    sf::Music& music = get(id);

    if (currentMusicId_ != id && !currentMusicId_.empty()) {
        resources_[currentMusicId_]->stop();
    }

    music.setLooping(loop);
    music.setVolume(volume);
    music.setRelativeToListener(false);
    music.play();

    currentMusicId_ = id;
}

void MusicManager::pause()
{
    if (!currentMusicId_.empty()) {
        resources_[currentMusicId_]->pause();
    }
}

void MusicManager::resume()
{
    if (!currentMusicId_.empty()) {
        resources_[currentMusicId_]->play();
    }
}

void MusicManager::stop()
{
    if (!currentMusicId_.empty()) {
        auto& music = *resources_[currentMusicId_];
        music.stop();
        currentMusicId_.clear();
    }
}

void MusicManager::setVolume(float volume)
{
    if (!currentMusicId_.empty()) {
        resources_[currentMusicId_]->setVolume(volume);
    }
}
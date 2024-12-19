#include "../include/ResourceManager.hpp"
#include <iostream>

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

bool ResourceManager::loadTexture(const std::string& name, const std::string& filename) {
    Texture texture;
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        return false;
    }
    textures[name] = texture;
    return true;
}

Texture& ResourceManager::getTexture(const std::string& name) {
    return textures.at(name);
}

bool ResourceManager::loadSound(const std::string& name, const std::string& filename) {
    SoundBuffer sound;
    if (!sound.loadFromFile(filename)) {
        std::cerr << "Failed to load sound: " << filename << std::endl;
        return false;
    }
    sounds[name] = sound;
    return true;
}

SoundBuffer& ResourceManager::getSound(const std::string& name) {
    return sounds.at(name);
}
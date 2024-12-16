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

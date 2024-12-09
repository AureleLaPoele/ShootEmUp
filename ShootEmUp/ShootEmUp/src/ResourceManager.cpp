#include "../include/ResourceManager.hpp"
#include <stdexcept>

ResourceManager& ResourceManager::getInstance() {
	static ResourceManager instance;
	return instance;
}

bool ResourceManager::loadTexture(const std::string& name, const std::string& filename) {
	Texture texture;
	if (!texture.loadFromFile(filename)) {
		return -1;
	}
	textures[name] = std::move(texture);
	return true;
}

Texture& ResourceManager::getTexture(const std::string& name) {
	if (textures.find(name) == textures.end()) {
		throw std::runtime_error("Texture non trouvée : " + name);
	}
	return textures.at(name);
}
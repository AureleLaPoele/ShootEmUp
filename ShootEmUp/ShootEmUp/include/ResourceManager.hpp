#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
using namespace sf;

class ResourceManager {
public:
	static ResourceManager& getInstance();

	// Méthode pour charger les ressources
	bool loadTexture(const std::string& name, const std::string& filename); // Ressource texture seulement pour l'instant
	Texture& getTexture(const std::string& name);

private:
	ResourceManager() = default;

	std::unordered_map<std::string, Texture> textures;
};

#endif
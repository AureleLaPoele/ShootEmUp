#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include "main.hpp"
using namespace sf;

class ResourceManager {
public:
    static ResourceManager& getInstance();

    // Method to load resources
    bool loadTexture(const std::string& name, const std::string& filename); // Resource texture only for now
    Texture& getTexture(const std::string& name);
    bool loadSound(const std::string& name, const std::string& filename);
    SoundBuffer& getSound(const std::string& name);

private:
    ResourceManager() = default;

    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, SoundBuffer> sounds;
};

#endif

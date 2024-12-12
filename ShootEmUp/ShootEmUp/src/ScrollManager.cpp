#include "../include/ScrollManager.hpp"

ScrollManager::ScrollManager(float scrollSpeed, const sf::Vector2u& windowSize)
    : baseScrollSpeed(scrollSpeed), windowSize(windowSize) {}

void ScrollManager::addLayer(const std::vector<sf::Texture>& textures, float scale, float layerSpeed) {
    if (textures.empty()) return;

    Layer layer;
    layer.speed = layerSpeed;

    for (const auto& texture : textures) {
        sf::Sprite sprite(texture);
        sprite.setScale(scale, scale);
        layer.sprites.push_back(sprite);
    }

    layer.sprites[0].setPosition(0, 0);
    if (layer.sprites.size() > 1) {
        layer.sprites[1].setPosition(0, textures[0].getSize().y * scale);
    }

    layers.push_back(layer);
}

void ScrollManager::update(float deltaTime) {
    for (auto& layer : layers) {
        float offset = baseScrollSpeed * layer.speed * deltaTime;

        for (auto& sprite : layer.sprites) {
            sprite.move(0, offset);

            if (sprite.getPosition().y >= windowSize.y) {
                sprite.setPosition(0, -sprite.getGlobalBounds().height + sprite.getPosition().y - windowSize.y);
            }
        }
    }
}

void ScrollManager::draw(sf::RenderWindow& window) {
    for (const auto& layer : layers) {
        for (const auto& sprite : layer.sprites) {
            window.draw(sprite);
        }
    }
}

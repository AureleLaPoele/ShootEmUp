// PowerUp.cpp
#include "PowerUp.hpp"

PowerUp::PowerUp(Type type, const sf::Texture& texture, sf::Vector2f position)
    : type(type), active(true) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void PowerUp::draw(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

bool PowerUp::checkCollision(const sf::Sprite& playerSprite) {
    if (active && sprite.getGlobalBounds().intersects(playerSprite.getGlobalBounds())) {
        active = false; // Mark as collected
        return true;
    }
    return false;
}

PowerUp::Type PowerUp::getType() const {
    return type;
}

bool PowerUp::isActive() const {
    return active;
}
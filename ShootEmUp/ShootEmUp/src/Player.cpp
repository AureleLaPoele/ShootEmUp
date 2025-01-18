#include "../include/Player.hpp"
#include "../include/ResourceManager.hpp"
#include "../include/ProjectileManager.hpp"

Player::Player() : Ship(100) {}

int Player::loadTexture() {
    auto& resourceManager = ResourceManager::getInstance();
    if (!resourceManager.loadTexture("playerShipTexture", "assets/sprites/Player_ship_v1.png")) {
        std::cerr << "Failed to load player ship texture." << std::endl;
        return -1;
    }
    this->playerShip.setTexture(resourceManager.getTexture("playerShipTexture"));
    this->playerShip.setPosition(250, 700);
}

void Player::move(const std::unordered_map<sf::Keyboard::Key, bool>& keyStates, float speed, const sf::RenderWindow& window) {
    float dx = 0.0f, dy = 0.0f;

    if (keyStates.at(sf::Keyboard::Z)) dy -= speed;
    if (keyStates.at(sf::Keyboard::S)) dy += speed;
    if (keyStates.at(sf::Keyboard::Q)) dx -= speed;
    if (keyStates.at(sf::Keyboard::D)) dx += speed;

    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    sf::FloatRect bounds = this->playerShip.getGlobalBounds();
    if (this->playerShip.getPosition().x + dx < 0 || this->playerShip.getPosition().x + bounds.width + dx > window.getSize().x) dx = 0;
    if (this->playerShip.getPosition().y + dy < 0 || this->playerShip.getPosition().y + bounds.height + dy > window.getSize().y) dy = 0;

    this->playerShip.move(dx, dy);
}

void Player::shot(ProjectileManager& projectileManager, const std::unordered_map<sf::Keyboard::Key, bool>& keyStates) {
    if (keyStates.at(sf::Keyboard::Space)) {
        projectileManager.handlePlayerInput(sf::Keyboard::Space, this->playerShip.getPosition());
    }
}

bool Player::isTouch(ProjectileManager& projectileManager, sf::Sprite player) {
    for (auto it = projectileManager.playerProjectiles.begin(); it != projectileManager.playerProjectiles.end(); ) {
        if (player.getGlobalBounds().intersects(it->sprite.getGlobalBounds())) {
            it = projectileManager.playerProjectiles.erase(it);
            return true;
        }
        else {
            ++it;
        }
    }
    return false;
}


#include "../include/Enemy.hpp"
#include "../include/ResourceManager.hpp"

Enemy::Enemy() : Ship(100) {}

int Enemy::loadTextureBasic() {
    auto& resourceManager = ResourceManager::getInstance();
    if (!resourceManager.loadTexture("basicShipTexture", "assets/sprites/Enemy_basic_v1.png")) {
        std::cerr << "Failed to load player ship texture." << std::endl;
        return -1;
    }
    this->enemyShipBasic.setTexture(resourceManager.getTexture("basicShipTexture"));
    this->enemyShipBasic.setPosition(30, 30);
}


void Enemy::level1() {
    this->loadTextureBasic();
}

void Enemy::move(const sf::RenderWindow& window, int cycle) {
    float dx = 0.0f, dy = 0.0f;
    if (cycle != 5) {
        dx = 10.0f;
    }
    enemyShipBasic.move(dx, dy);
}

void Enemy::shot(ProjectileManager& projectileManager) {
    projectileManager.spawnEnemyProjectile(sf::Keyboard::Space, this->enemyShipBasic.getPosition());
}
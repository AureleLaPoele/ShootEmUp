#include "../include/Enemy.hpp"
#include "../include/ProjectileManager.hpp"
#include <vector>

Enemy::Enemy() : Ship(100) {}

int Enemy::loadTextureBasic() {
    auto& resourceManager = ResourceManager::getInstance();
    if (!resourceManager.loadTexture("basicShipTexture", "assets/sprites/Enemy_basic_v1.png")) {
        std::cerr << "Failed to load basic enemy ship texture." << std::endl;
        return -1;
    }
    this->enemyShipBasic.setTexture(resourceManager.getTexture("basicShipTexture"));
    this->enemyShipBasic.setPosition(30, 30);
}

int Enemy::loadTextureAdvanced() {
    auto& resourceManager = ResourceManager::getInstance();
    if (!resourceManager.loadTexture("advancedShipTexture", "assets/sprites/Enemy_advanced_v1.png")) {
        std::cerr << "Failed to load advanced enemy ship texture." << std::endl;
        return -1;
    }
    this->enemyShipAdvanced.setTexture(resourceManager.getTexture("advancedShipTexture"));
    this->enemyShipAdvanced.setPosition(30, 30);
}

int Enemy::loadTextureBoss() {
    auto& resourceManager = ResourceManager::getInstance();
    if (!resourceManager.loadTexture("bossShipTexture", "assets/sprites/Enemy_boss_v1.png")) {
        std::cerr << "Failed to load boss enemy ship texture." << std::endl;
        return -1;
    }
    this->enemyShipBoss.setTexture(resourceManager.getTexture("bossShipTexture"));
    this->enemyShipBoss.setPosition(30, 30);
}


void Enemy::level1() {
    this->loadTextureBasic();
}

void Enemy::level2() {
    this->loadTextureAdvanced();
}

void Enemy::level3() {
    this->loadTextureAdvanced();
}

void Enemy::move(const sf::RenderWindow& window, int cycle) {
    float dx = 0.0f, dy = 0.0f;
    if (cycle != 5) {
        dx = 10.0f;
    }
    enemyShipBasic.move(dx, dy);
}

void Enemy::shot(ProjectileManager& projectileManager) {
    projectileManager.spawnEnemyProjectile(this->enemyShipBasic.getPosition());
}

bool Enemy::isTouch(ProjectileManager& projectileManager, sf::Sprite player) {
    for (auto it = projectileManager.enemyProjectiles.begin(); it != projectileManager.enemyProjectiles.end(); ) {
        if (player.getGlobalBounds().intersects(it->sprite.getGlobalBounds())) {
            it = projectileManager.enemyProjectiles.erase(it);
            return true;
        }
        else {
            ++it;
        }
    }

    return false;
}
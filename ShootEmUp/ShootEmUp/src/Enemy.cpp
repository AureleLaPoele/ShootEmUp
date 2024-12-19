#include "../include/Enemy.hpp"
#include "../include/ProjectileManager.hpp"
#include <vector>

Enemy::Enemy() : Ship(100) {}

int Enemy::loadTextureBasic(int x, int y) {
    auto& resourceManager = ResourceManager::getInstance();
    if (!resourceManager.loadTexture("basicShipTexture", "assets/sprites/Enemy_basic_v1.png")) {
        std::cerr << "Failed to load basic enemy ship texture." << std::endl;
        return -1;
    }
    this->enemyShipBasic.setTexture(resourceManager.getTexture("basicShipTexture"));
    this->enemyShipBasic.setPosition(x, y);
}

int Enemy::loadTextureAdvanced(int x, int y) {
    auto& resourceManager = ResourceManager::getInstance();
    if (!resourceManager.loadTexture("advancedShipTexture", "assets/sprites/Enemy_advanced_v1.png")) {
        std::cerr << "Failed to load advanced enemy ship texture." << std::endl;
        return -1;
    }
    this->enemyShipAdvanced.setTexture(resourceManager.getTexture("advancedShipTexture"));
    this->enemyShipAdvanced.setPosition(x, y);
}

int Enemy::loadTextureBoss(int x, int y) {
    auto& resourceManager = ResourceManager::getInstance();
    if (!resourceManager.loadTexture("bossShipTexture", "assets/sprites/Enemy_boss_v1.png")) {
        std::cerr << "Failed to load boss enemy ship texture." << std::endl;
        return -1;
    }
    this->enemyShipBoss.setTexture(resourceManager.getTexture("bossShipTexture"));
    this->enemyShipBoss.setPosition(x, y);
}

void Enemy::move(const sf::RenderWindow& window, int cycle) {
    float dx = 0.0f, dy = 0.0f;
    if (cycle <= 10) {
        dx = 10.0f;
    }
    else if (cycle == 11) {
        dy = 20.0f;
    }
    else if (cycle <= 21) {
        dx = -10.0f;
    }
    else if (cycle == 22) {
        dy = 20.0f;
    }
    enemyShipBasic.move(dx, dy);
    enemyShipAdvanced.move(dx, dy);
}

void Enemy::shot(ProjectileManager& projectileManager, int random) {
    if (random == 99) {
        projectileManager.spawnEnemyProjectile(this->enemyShipBasic.getPosition());
    }
}

void Enemy::shotAdvanced(ProjectileManager& projectileManager, int random) {
    if (random == 99) {
        projectileManager.spawnEnemyProjectile(this->enemyShipAdvanced.getPosition());
    }
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
#include "../include/Enemy.hpp"
#include "../include/ResourceManager.hpp"

Enemy::Enemy() : Ship(100) {}

int Enemy::loadTextureBasic() {
    auto& resourceManager = ResourceManager::getInstance();
    if (!resourceManager.loadTexture("basicShipTexture", "assets/sprites/Player_ship_v1.png")) {
        std::cerr << "Failed to load player ship texture." << std::endl;
        return -1;
    }
    this->enemyShipBasic.setTexture(resourceManager.getTexture("basicShipTexture"));
}


void Enemy::level1() {
    this->loadTextureBasic();
}
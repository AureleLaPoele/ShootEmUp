#include "Enemy.hpp"

// Constructor that directly loads the texture
Enemy::Enemy(const string& textureFile, int hp, int pow, float fr, int nb)
    : health(hp), power(pow), fireRate(fr), nbBullets(nb) {
    // Load the texture from file
    if (!EnemyTexture.loadFromFile(textureFile)) {
        cerr << "Error: Could not load texture file: " << textureFile << endl;
    }
    // Assign the texture to the sprite
    EnemyShip.setTexture(EnemyTexture);
}


// Method to get the sprite's position (coordinates)
Vector2f Enemy::getPosition() const {
    return EnemyShip.getPosition();
}

// Method to set the position of the sprite
void Enemy::setPosition(float x, float y) {
    EnemyShip.setPosition(x, y);
}

// Getter for the sprite
Sprite& Enemy::getSprite() {
    return EnemyShip;
}

// Getter for health
int Enemy::getHealth() const {
    return health;
}

// Getter for power
int Enemy::getPower() const {
    return power;
}

// Getter for fire rate
float Enemy::getFireRate() const {
    return fireRate;
}

// Getter for the number of bullets
int Enemy::getNbBullets() const {
    return nbBullets;
}

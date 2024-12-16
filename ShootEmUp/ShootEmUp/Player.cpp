#include "Player.hpp"

// Constructor that directly loads the texture
Player::Player(const string& textureFile, int hp, int pow, float fr, int nb)
    : health(hp), power(pow), fireRate(fr), nbBullets(nb) {
    // Load the texture from file
    if (!PlayerTexture.loadFromFile(textureFile)) {
        cerr << "Error: Could not load texture file: " << textureFile << endl;
    }
    // Assign the texture to the sprite
    PlayerShip.setTexture(PlayerTexture);
}

// Method to get the sprite's position (coordinates)
Vector2f Player::getPosition() const {
    return PlayerShip.getPosition();
}

// Method to set the position of the sprite
void Player::setPosition(float x, float y) {
    PlayerShip.setPosition(x, y);
}

// Getter for the sprite
Sprite& Player::getSprite() {
    return PlayerShip;
}

// Getter for health
int Player::getHealth() const {
    return health;
}

// Getter for power
int Player::getPower() const {
    return power;
}

// Getter for fire rate
float Player::getFireRate() const {
    return fireRate;
}

// Getter for the number of bullets
int Player::getNbBullets() const {
    return nbBullets;
}

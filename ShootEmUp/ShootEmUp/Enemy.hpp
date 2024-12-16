#ifndef Enemy_HPP
#define Enemy_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

class Enemy {
private:
    Sprite EnemyShip;
    Texture EnemyTexture; // Store the texture as a member
    int health;
    int power;
    float fireRate;
    int nbBullets;

public:
    // Constructor that directly loads the texture
    Enemy(const string& textureFile, int hp, int pow, float fr, int nb);

    // Method to get the sprite's position (coordinates)
    Vector2f getPosition() const;

    // Method to set the position of the sprite
    void setPosition(float x, float y);

    // Getters
    Sprite& getSprite();
    int getHealth() const;
    int getPower() const;
    float getFireRate() const;
    int getNbBullets() const;
};

#endif // Enemy_HPP

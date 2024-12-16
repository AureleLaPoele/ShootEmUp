#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

class Player {
private:
    Sprite PlayerShip;
    Texture PlayerTexture; // Store the texture as a member
    int health;
    int power;
    float fireRate;
    int nbBullets;

public:
    // Constructor that directly loads the texture
    Player(const string& textureFile, int hp, int pow, float fr, int nb);

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

#endif // PLAYER_HPP

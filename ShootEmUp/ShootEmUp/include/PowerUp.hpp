#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <SFML/Graphics.hpp>

class PowerUp {
public:
    enum Type { DamageUp, FireRateUp, BulletsUp }; // Specific power-up types

    // Constructor
    PowerUp(Type type, const sf::Texture& texture, sf::Vector2f position);

    // Draw the power-up if active
    void draw(sf::RenderWindow& window);

    // Check collision with player
    bool checkCollision(const sf::Sprite& playerSprite);

    // Get the type of the power-up
    Type getType() const;

    // Check if the power-up is still active
    bool isActive() const;

private:
    Type type;
    sf::Sprite sprite;
    bool active;
};

#endif // POWERUP_HPP

#ifndef PROJECTILE_MANAGER_HPP
#define PROJECTILE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class ProjectileManager {
public:
    ProjectileManager(float screenWidth, float screenHeight, const sf::Texture& playerTexture, const sf::Texture& enemyTexture);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void handlePlayerInput(const sf::Keyboard::Key& key, const sf::Vector2f& playerPosition);

    void spawnEnemyProjectile(const sf::Vector2f& position, const sf::Vector2f& velocity);

private:
    struct Projectile {
        sf::Sprite sprite;
        sf::Vector2f velocity;

        Projectile(const sf::Vector2f& position, const sf::Vector2f& velocity, const sf::Texture& texture)
            : velocity(velocity) {
            sprite.setTexture(texture);
            sprite.setPosition(position);
        }
    };

    std::vector<Projectile> playerProjectiles;
    std::vector<Projectile> enemyProjectiles;

    float screenWidth;
    float screenHeight;
    bool isSpacePressed;

    const sf::Texture& playerProjectileTexture;
    const sf::Texture& enemyProjectileTexture;

    float shotCooldown;
    float timeSinceLastShot;

    void removeOffScreenProjectiles(std::vector<Projectile>& projectiles);
};

#endif // PROJECTILE_MANAGER_HPP

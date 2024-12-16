#ifndef ENEMY_MANAGER_HPP
#define ENEMY_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "ProjectileManager.hpp"  // Include the ProjectileManager header

class EnemyManager {
public:
    EnemyManager(float screenWidth, float screenHeight, const sf::Texture& enemyTexture, const sf::Texture& enemyProjectileTexture, ProjectileManager& projectileManager);

    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    //void spawnEnemy();
    void removeOffScreenEnemies();
    void handleEnemyShooting(float deltaTime);

private:
    struct Enemy {
        sf::Sprite sprite;
        sf::Vector2f velocity;
        float timeSinceLastShot;

        Enemy(const sf::Vector2f& position, const sf::Vector2f& velocity, const sf::Texture& texture)
            : velocity(velocity), timeSinceLastShot(0.0f) {
            sprite.setTexture(texture);
            sprite.setPosition(position);
        }
    };

    std::vector<Enemy> enemies;
    float screenWidth;
    float screenHeight;
    float spawnCooldown;
    float timeSinceLastSpawn;

    const sf::Texture& enemyTexture;
    const sf::Texture& enemyProjectileTexture;

    ProjectileManager& projectileManager; // Reference to the ProjectileManager to handle projectiles

    void spawnRandomEnemy();
};

#endif // ENEMY_MANAGER_HPP

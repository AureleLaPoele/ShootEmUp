#include "../include/EnemyManager.hpp"
#include <cstdlib>
#include <ctime>

EnemyManager::EnemyManager(float screenWidth, float screenHeight, const sf::Texture& enemyTexture, const sf::Texture& enemyProjectileTexture, ProjectileManager& projectileManager)
    : screenWidth(screenWidth), screenHeight(screenHeight),
    enemyTexture(enemyTexture), enemyProjectileTexture(enemyProjectileTexture),
    projectileManager(projectileManager), spawnCooldown(2.0f), timeSinceLastSpawn(0.0f) {
    std::srand(static_cast<unsigned int>(std::time(0))); // Seed the random number generator
}

void EnemyManager::update(float deltaTime) {
    timeSinceLastSpawn += deltaTime;

    // Spawn new enemies if the cooldown has passed
    if (timeSinceLastSpawn >= spawnCooldown) {
        spawnRandomEnemy();
        timeSinceLastSpawn = 0.0f;
    }

    // Update the enemies
    for (auto& enemy : enemies) {
        enemy.sprite.move(enemy.velocity * deltaTime);
        enemy.timeSinceLastShot += deltaTime;

        // Handle enemy shooting
        handleEnemyShooting(deltaTime);
    }

    // Remove off-screen enemies
    removeOffScreenEnemies();
}

void EnemyManager::render(sf::RenderWindow& window) {
    for (const auto& enemy : enemies) {
        window.draw(enemy.sprite);
    }
}

void EnemyManager::spawnRandomEnemy() {
    // Random position for spawning enemies (at the top of the screen)
    float xPosition = static_cast<float>(std::rand() % static_cast<int>(screenWidth - 50));
    float yPosition = -50.0f; // Start above the screen

    // Random velocity for movement (downwards and a little horizontal)
    float xVelocity = static_cast<float>((std::rand() % 100) - 50) / 100.0f;
    float yVelocity = 100.0f;

    // Create a new enemy and add it to the list
    enemies.emplace_back(sf::Vector2f(xPosition, yPosition), sf::Vector2f(xVelocity, yVelocity), enemyTexture);
}

void EnemyManager::removeOffScreenEnemies() {
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(), [this](const Enemy& enemy) {
            const sf::Vector2f& pos = enemy.sprite.getPosition();
            return pos.y > screenHeight;
            }),
        enemies.end()
    );
}

void EnemyManager::handleEnemyShooting(float deltaTime) {
    for (auto& enemy : enemies) {
        // Shoot a projectile every 3 seconds
        if (enemy.timeSinceLastShot >= 3.0f) {
            // Position the projectile at the center of the enemy
            sf::Vector2f projectilePosition(enemy.sprite.getPosition().x + enemy.sprite.getGlobalBounds().width / 2,
                enemy.sprite.getPosition().y + enemy.sprite.getGlobalBounds().height);
            sf::Vector2f projectileVelocity(0, 250); // Downward velocity

            // Use ProjectileManager to spawn the projectile
            projectileManager.spawnEnemyProjectile(projectilePosition, projectileVelocity);

            enemy.timeSinceLastShot = 0.0f;
        }
    }
}

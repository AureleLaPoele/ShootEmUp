#include "../include/ProjectileManager.hpp"
#include <algorithm>

ProjectileManager::ProjectileManager(float screenWidth, float screenHeight, const sf::Texture& playerTexture, const sf::Texture& enemyTexture)
    : screenWidth(screenWidth), screenHeight(screenHeight), isSpacePressed(false),
    shotCooldown(0.5f), timeSinceLastShot(0.0f),
    playerProjectileTexture(playerTexture), enemyProjectileTexture(enemyTexture) {}

void ProjectileManager::update(float deltaTime) {
    // Update cooldown timer
    timeSinceLastShot += deltaTime;

    // Update player projectiles
    for (auto& projectile : playerProjectiles) {
        projectile.sprite.move(projectile.velocity * deltaTime);
    }
    removeOffScreenProjectiles(playerProjectiles);

    // Update enemy projectiles
    for (auto& projectile : enemyProjectiles) {
        projectile.sprite.move(projectile.velocity * deltaTime);
    }
    removeOffScreenProjectiles(enemyProjectiles);
}

void ProjectileManager::render(sf::RenderWindow& window) {
    for (const auto& projectile : playerProjectiles) {
        window.draw(projectile.sprite);
    }
    for (const auto& projectile : enemyProjectiles) {
        window.draw(projectile.sprite);
    }
}

void ProjectileManager::handlePlayerInput(const sf::Keyboard::Key& key, const sf::Vector2f& playerPosition) {
    // Check if the spacebar is pressed and if the cooldown has elapsed
    if (key == sf::Keyboard::Space && timeSinceLastShot >= shotCooldown) {
        // Adjust spawn position relative to player
        sf::Vector2f spawnPosition(playerPosition.x + 10, playerPosition.y - 10);
        sf::Vector2f velocity(0, -350); // Upward velocity

        playerProjectiles.emplace_back(spawnPosition, velocity, playerProjectileTexture);
        timeSinceLastShot = 0.0f; // Reset cooldown timer
    }
}

void ProjectileManager::spawnEnemyProjectile(const sf::Vector2f& position, const sf::Vector2f& velocity) {
    enemyProjectiles.emplace_back(position, velocity, enemyProjectileTexture);
}

void ProjectileManager::removeOffScreenProjectiles(std::vector<Projectile>& projectiles) {
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(), [this](const Projectile& p) {
            const sf::Vector2f& pos = p.sprite.getPosition();
            return pos.x < 0 || pos.x > screenWidth || pos.y < 0 || pos.y > screenHeight;
            }),
        projectiles.end()
    );
}

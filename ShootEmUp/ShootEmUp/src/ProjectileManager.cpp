#include "../include/ProjectileManager.hpp"

using namespace sf;
using namespace std;

ProjectileManager::ProjectileManager(float screenWidth, float screenHeight, const Texture& playerTexture, const Texture& enemyTexture)
    : screenWidth(screenWidth), screenHeight(screenHeight), isSpacePressed(false),
    shotCooldown(0.5f), timeSinceLastShot(0.0f),
    playerProjectileTexture(playerTexture), enemyProjectileTexture(enemyTexture) {}

void ProjectileManager::update(float deltaTime) {
    timeSinceLastShot += deltaTime;

    for (auto& projectile : playerProjectiles) {
        projectile.sprite.move(projectile.velocity * deltaTime);
    }
    removeOffScreenProjectiles(playerProjectiles);

    for (auto& projectile : enemyProjectiles) {
        projectile.sprite.move(projectile.velocity * deltaTime);
    }
    removeOffScreenProjectiles(enemyProjectiles);
}

void ProjectileManager::render(RenderWindow& window) {
    for (const auto& projectile : playerProjectiles) {
        window.draw(projectile.sprite);
    }
    for (const auto& projectile : enemyProjectiles) {
        window.draw(projectile.sprite);
    }
}

void ProjectileManager::handlePlayerInput(const sf::Keyboard::Key& key) {
    // Check if the spacebar is pressed and if the cooldown has elapsed
    if (key == sf::Keyboard::Space && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (timeSinceLastShot >= shotCooldown) {
            playerProjectiles.emplace_back(
                sf::Vector2f(screenWidth / 1.5, screenHeight - 50), // Initial position
                sf::Vector2f(0, -300),                            // Upward velocity
                playerProjectileTexture                           // Texture
            );

            timeSinceLastShot = 0.0f; // Reset cooldown timer
        }
    }
}


void ProjectileManager::spawnEnemyProjectile(const Vector2f& position, const Vector2f& velocity) {
    enemyProjectiles.emplace_back(position, velocity, enemyProjectileTexture);
}

void ProjectileManager::removeOffScreenProjectiles(std::vector<Projectile>& projectiles) {
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(), [this](const Projectile& p) {
            const Vector2f& pos = p.sprite.getPosition();
            return pos.x < 0 || pos.x > screenWidth || pos.y < 0 || pos.y > screenHeight;
            }),
        projectiles.end()
    );
}

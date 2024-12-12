#include "include/main.hpp"
#include <unordered_map>
#include <iostream>

// Function declarations
void HandleShootingInput(ProjectileManager& projectileManager, const sf::Sprite& playerShip, const std::unordered_map<sf::Keyboard::Key, bool>& keyStates);
void HandleMovementInput(sf::Sprite& sprite, const std::unordered_map<sf::Keyboard::Key, bool>& keyStates, float speed, const sf::RenderWindow& window);

int main() {
    // Window creation
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "Shoot Them Up");
    window.setVerticalSyncEnabled(true);

    auto& resourceManager = ResourceManager::getInstance();
    if (!resourceManager.loadTexture("playerShipTexture", "assets/sprites/Player_ship_v1.png")) {
        std::cerr << "Failed to load player ship texture." << std::endl;
        return -1;
    }

    sf::Sprite playerShip;
    playerShip.setTexture(resourceManager.getTexture("playerShipTexture"));
    playerShip.setPosition(250, 700);

    // Load laser textures
    if (!resourceManager.loadTexture("playerLaser", "assets/Player_laser.png") ||
        !resourceManager.loadTexture("enemyLaser", "assets/Enemy_laser.png")) {
        std::cerr << "Failed to load laser textures." << std::endl;
        return -1;
    }

    // Create a ProjectileManager instance
    ProjectileManager projectileManager(static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y),
        resourceManager.getTexture("playerLaser"),
        resourceManager.getTexture("enemyLaser"));

    // Define movement speed
    const float speed = 5.0f;

    // Track key states (initialize all required keys)
    std::unordered_map<sf::Keyboard::Key, bool> keyStates = {
        {sf::Keyboard::Z, false},
        {sf::Keyboard::S, false},
        {sf::Keyboard::Q, false},
        {sf::Keyboard::D, false},
        {sf::Keyboard::Space, false}
    };

    // Game Loop
    sf::Clock cooldown;
    while (window.isOpen()) {
        // Poll events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                keyStates[event.key.code] = true;
            }
            if (event.type == sf::Event::KeyReleased) {
                keyStates[event.key.code] = false;
            }
        }

        // Handle continuous input for movement and shooting
        HandleMovementInput(playerShip, keyStates, speed, window);
        HandleShootingInput(projectileManager, playerShip, keyStates);

        // Calculate deltaTime
        float deltaTime = cooldown.restart().asSeconds();

        // Update the projectile manager
        projectileManager.update(deltaTime);

        // Render
        window.clear();
        projectileManager.render(window);
        window.draw(playerShip);
        window.display();
    }

    return 0;
}

void HandleMovementInput(sf::Sprite& sprite, const std::unordered_map<sf::Keyboard::Key, bool>& keyStates, float speed, const sf::RenderWindow& window) {
    float dx = 0.0f, dy = 0.0f;

    // Check key states for movement
    if (keyStates.at(sf::Keyboard::Z)) dy -= speed;
    if (keyStates.at(sf::Keyboard::S)) dy += speed;
    if (keyStates.at(sf::Keyboard::Q)) dx -= speed;
    if (keyStates.at(sf::Keyboard::D)) dx += speed;

    // Normalize diagonal movement to maintain consistent speed
    if (dx != 0 && dy != 0) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    // Boundary checks
    sf::FloatRect bounds = sprite.getGlobalBounds();
    if (sprite.getPosition().x + dx < 0 || sprite.getPosition().x + bounds.width + dx > window.getSize().x) dx = 0;
    if (sprite.getPosition().y + dy < 0 || sprite.getPosition().y + bounds.height + dy > window.getSize().y) dy = 0;

    // Apply movement
    sprite.move(dx, dy);
}

void HandleShootingInput(ProjectileManager& projectileManager, const sf::Sprite& playerShip, const std::unordered_map<sf::Keyboard::Key, bool>& keyStates) {
    if (keyStates.at(sf::Keyboard::Space)) {
        projectileManager.handlePlayerInput(sf::Keyboard::Space, playerShip.getPosition());
    }
}

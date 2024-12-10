#include "include/main.hpp"
#include <unordered_map>

// Function declarations
void HandleShootingInput(ProjectileManager& projectileManager, const sf::Sprite& playerShip, const std::unordered_map<sf::Keyboard::Key, bool>& keyStates);
void HandleMovementInput(sf::Sprite& sprite, const std::unordered_map<sf::Keyboard::Key, bool>& keyStates, float speed, const sf::RenderWindow& window);

int main() {
    // Window creation
    RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "Title");
    window.setVerticalSyncEnabled(true);

    auto& resourceManager = ResourceManager::getInstance();
    resourceManager.loadTexture("playerShipTexture", "assets/sprites/Player_ship_v1.png");
    sf::Sprite playerShipTexture;
    playerShipTexture.setTexture(resourceManager.getTexture("playerShipTexture"));
    playerShipTexture.setPosition(500, 200);

    // Load laser textures
    Texture playerLaserTexture;
    Texture enemyLaserTexture;

    if (!playerLaserTexture.loadFromFile("assets/Player_laser.png")) {
        cerr << "Error loading Player_laser.png" << endl;
        return -1;
    }
    if (!enemyLaserTexture.loadFromFile("assets/Enemy_laser.png")) {
        cerr << "Error loading Enemy_laser.png" << endl;
        return -1;
    }

    // Create a ProjectileManager instance
    ProjectileManager projectileManager(static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y),
        playerLaserTexture,
        enemyLaserTexture);

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

    // cooldown for timing
    sf::Clock cooldown;

    // Game Loop
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
        HandleMovementInput(playerShipTexture, keyStates, speed, window);
        HandleShootingInput(projectileManager, playerShipTexture, keyStates);

        // Calculate deltaTime
        float deltaTime = cooldown.restart().asSeconds();

        // Update the projectile manager
        projectileManager.update(deltaTime);

        // Render
        window.clear();
        projectileManager.render(window);
        window.draw(playerShipTexture);
        window.display();
    }

    return 0;
}

void HandleMovementInput(sf::Sprite& sprite, const std::unordered_map<sf::Keyboard::Key, bool>& keyStates, float speed, const sf::RenderWindow& window) {
    float dx = 0.0f, dy = 0.0f;

    // Check key states for movement
    if (keyStates.find(sf::Keyboard::Z) != keyStates.end() && keyStates.at(sf::Keyboard::Z)) dy -= speed;
    if (keyStates.find(sf::Keyboard::S) != keyStates.end() && keyStates.at(sf::Keyboard::S)) dy += speed;
    if (keyStates.find(sf::Keyboard::Q) != keyStates.end() && keyStates.at(sf::Keyboard::Q)) dx -= speed;
    if (keyStates.find(sf::Keyboard::D) != keyStates.end() && keyStates.at(sf::Keyboard::D)) dx += speed;

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
    if (keyStates.find(sf::Keyboard::Space) != keyStates.end() && keyStates.at(sf::Keyboard::Space)) {
        projectileManager.handlePlayerInput(sf::Keyboard::Space, playerShip.getPosition());
    }
}

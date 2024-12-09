#include "include/main.hpp"
#include <unordered_map>

void HandleMovementInput(Sprite& sprite, const unordered_map<Keyboard::Key, bool>& keyStates, float speed);
void HandleShootingInput(ProjectileManager& projectileManager, const unordered_map<Keyboard::Key, bool>& keyStates);

int main() {
    // Création window
    RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "Title");
    // V-sync
    window.setVerticalSyncEnabled(true);

    auto& resourceManager = ResourceManager::getInstance();
    resourceManager.loadTexture("playerShipTexture", "assets/sprites/Player_ship_v1.png");
    sf::Sprite playerShipTexture(resourceManager.getTexture("playerShipTexture"));

    //resourceManager.loadTexture("playerLaserTexture", "assets/sprites/Player_laser.png");
    //sf::Sprite playerLaserTexture(resourceManager.getTexture("playerLaserTexture"));

    //resourceManager.loadTexture("playerShipTexture", "assets/sprites/Player_ship_v1.png");
    //sf::Sprite playerShipTexture(resourceManager.getTexture("playerShipTexture"));
    // 

    // Load textures
    Texture playerLaserTexture;
    Texture enemyLaserTexture;

    if (!playerLaserTexture.loadFromFile("assets/Player_laser.png")) {
        cerr << "Error loading playerLaser textures" << endl;
        return -1; // Exit if textures cannot be loaded
    }
    if (!enemyLaserTexture.loadFromFile("assets/Enemy_laser.png")) {
        cerr << "Error loading enemyLaser textures" << endl;
        return -1; // Exit if textures cannot be loaded
    }

    playerShipTexture.setPosition(500, 200);

    // Create a ProjectileManager instance
    ProjectileManager projectileManager(800.0f, 600.0f, playerLaserTexture, enemyLaserTexture);

    // Define movement speed
    const float speed = 5.0f;

    // Track key states (initialize all required keys)
    unordered_map<Keyboard::Key, bool> keyStates = {
        {Keyboard::Z, false},
        {Keyboard::S, false},
        {Keyboard::Q, false},
        {Keyboard::D, false},
        {Keyboard::Space, false}
    };

    // cooldown for timing
    Clock cooldown;

    // Game Loop
    while (window.isOpen()) {
        // Poll events
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                keyStates[event.key.code] = true;
                cout << event.key.code << "    " << keyStates[event.key.code] << endl;
            }
            if (event.type == Event::KeyReleased) {
                keyStates[event.key.code] = false;
            }
        }

        // Handle continuous input for movement and shooting
        HandleMovementInput(playerShipTexture, keyStates, speed);
        HandleShootingInput(projectileManager, keyStates);

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

void HandleMovementInput(Sprite& sprite, const unordered_map<Keyboard::Key, bool>& keyStates, float speed) {
    // Movement vectors
    float dx = 0.0f;
    float dy = 0.0f;

    if (keyStates.at(Keyboard::Z)) {
        dy -= speed;
    }
    if (keyStates.at(Keyboard::S)) {
        dy += speed;
    }
    if (keyStates.at(Keyboard::Q)) {
        dx -= speed;
    }
    if (keyStates.at(Keyboard::D)) {
        dx += speed;
    }

    // Normalize diagonal movement to maintain consistent speed
    if (dx != 0 && dy != 0) {
        dx *= 0.7071f; // 1/sqrt(2)
        dy *= 0.7071f;
    }

    // Apply movement
    sprite.move(dx, dy);
}

void HandleShootingInput(ProjectileManager& projectileManager, const unordered_map<Keyboard::Key, bool>& keyStates) {
    // Check if the spacebar is pressed
    if (keyStates.at(Keyboard::Space)) {
        projectileManager.handlePlayerInput(Keyboard::Space);
    }
}

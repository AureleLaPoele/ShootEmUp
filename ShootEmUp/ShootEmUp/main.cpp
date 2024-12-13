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

    //Ressource manager et appel des textures
    auto& resourceManager = ResourceManager::getInstance();
    if (!resourceManager.loadTexture("playerShipTexture", "assets/sprites/Player_ship_v1.png")) {
        std::cerr << "Failed to load player ship texture." << std::endl;
        return -1;
    }

    if (!resourceManager.loadTexture("foregroundTexture", "assets/foreground.png")) {
        std::cerr << "Failed to load foreground texture." << std::endl;
        return -1;
    }

    if (!resourceManager.loadTexture("playerLaser", "assets/Player_laser.png") || !resourceManager.loadTexture("enemyLaser", "assets/Enemy_laser.png")) {
        std::cerr << "Failed to load laser textures." << std::endl;
        return -1;
    }

    std::vector<sf::Texture> frames;
    int frameCount = 14;
    for (int i = 0; i < frameCount; ++i) {
        sf::Texture texture;
        std::string filename = "assets/frames/frame" + std::to_string(i) + ".gif";
        if (!texture.loadFromFile(filename)) {
            return -1;
        }
        frames.push_back(texture);
    }

    sf::Sprite background1(frames[0]);
    sf::Sprite background2(frames[0]);

    sf::Sprite playerShip;
    playerShip.setTexture(resourceManager.getTexture("playerShipTexture"));
    playerShip.setPosition(250, 700);

    sf::Texture texture;
    texture = resourceManager.getTexture("foregroundTexture");
    sf::Sprite foregroundTexture;
    foregroundTexture.setTexture(resourceManager.getTexture("foregroundTexture"));
    sf::Sprite foreground1(foregroundTexture);
    sf::Sprite foreground2(foregroundTexture);
    float foregroundScaleFactor = 0.8f;

    float scaleX = static_cast<float>(window.getSize().x) / frames[0].getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / frames[0].getSize().y;
    float scaleXfore = static_cast<float>(window.getSize().x) / texture.getSize().x * foregroundScaleFactor;
    float scaleYfore = scaleXfore; // Garder le ratio d'aspect pour �viter l'�tirement

    background1.setScale(scaleX, scaleY);
    background2.setScale(scaleX, scaleY);
    foreground1.setScale(scaleXfore, scaleYfore);
    foreground2.setScale(scaleXfore, scaleYfore);

    background1.setPosition(0, 0);
    background2.setPosition(0, frames[0].getSize().y * scaleY);
    foreground1.setPosition(200, 0);
    foreground2.setPosition(200, texture.getSize().y * scaleYfore);

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

   
    sf::Clock cooldown;
    sf::Clock frameClock;
    sf::Clock scrollClock;
    int currentFrame = 0;
    float frameDuration = 0.1f;
    float scrollSpeed = 250.0f;
    float scrollSpeedforeground = 100.0f;

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

        // Animation
        if (frameClock.getElapsedTime().asSeconds() > frameDuration) {
            frameClock.restart();
            currentFrame = (currentFrame + 1) % frames.size(); // Passer � la frame suivante
            background1.setTexture(frames[currentFrame]);
            background2.setTexture(frames[currentFrame]);
        }

        // Handle continuous input for movement and shooting
        HandleMovementInput(playerShip, keyStates, speed, window);
        HandleShootingInput(projectileManager, playerShip, keyStates);

        // Calculate deltaTime and update the projectile manager
        float deltaTime = cooldown.restart().asSeconds();
        projectileManager.update(deltaTime);

        float offset = scrollSpeed * deltaTime;
        float offsetforeground = scrollSpeedforeground * deltaTime;
        background1.move(0, offset);
        background2.move(0, offset);
        foreground1.move(0, offsetforeground);
        foreground2.move(0, offsetforeground);

        if (background1.getPosition().y >= window.getSize().y) {
            background1.setPosition(0, background2.getPosition().y - background1.getGlobalBounds().height);
        }
        if (background2.getPosition().y >= window.getSize().y) {
            background2.setPosition(0, background1.getPosition().y - background2.getGlobalBounds().height);
        }
        if (foreground1.getPosition().y >= window.getSize().y) {
            foreground1.setPosition(0, foreground2.getPosition().y - foreground1.getGlobalBounds().height);
        }
        if (foreground2.getPosition().y >= window.getSize().y) {
            foreground2.setPosition(0, foreground1.getPosition().y - foreground2.getGlobalBounds().height);
        }

        // Render
        window.clear();
        window.draw(background1);
        window.draw(background2);
        window.draw(foreground1);
        window.draw(foreground2);
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

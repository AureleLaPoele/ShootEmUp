﻿#include "include/main.hpp"
#include <unordered_map>
#include <iostream>

// Function declarations
void HandleShootingInput(ProjectileManager& projectileManager, const sf::Sprite& playerShip, const std::unordered_map<sf::Keyboard::Key, bool>& keyStates);
void HandleMovementInput(sf::Sprite& sprite, const std::unordered_map<sf::Keyboard::Key, bool>& keyStates, float speed, const sf::RenderWindow& window);

int main() {

    std::cout << "test\n";
    std::cout << "test1\n";
    std::cout << "test2\n";
    std::cout << "test3\n";
    // Window creation
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "Shoot Them Up");
    window.setVerticalSyncEnabled(true);

    //Ressource manager et appel des textures

    sf::Font font;
    if (!font.loadFromFile("assets/RETROTECH.ttf")) {
        return -1;
    }

    auto& resourceManager = ResourceManager::getInstance();
    if (!resourceManager.loadTexture("playerShipTexture", "assets/sprites/Player_ship_v1.png")) {
        std::cerr << "Failed to load player ship texture." << std::endl;
        return -1;
    }

    if (!resourceManager.loadTexture("enemyBasicTexture", "assets/sprites/enemy_basic_v1.png")) {
        std::cerr << "Failed to load basic texture texture." << std::endl;
        return -1;
    }

    if (!resourceManager.loadTexture("enemyAdvancedTexture", "assets/sprites/enemy_Advanced_v1.png")) {
        std::cerr << "Failed to load enemy advanced texture." << std::endl;
        return -1;
    }

    if (!resourceManager.loadTexture("enemyEliteTexture", "assets/sprites/enemy_Elite_v1.png")) {
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

    if (!resourceManager.loadTexture("space", "assets/frames/frame0.gif")) {
        std::cerr << "Failed to load space texture." << std::endl;
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

    sf::Sprite enemyBasic;
    enemyBasic.setTexture(resourceManager.getTexture("enemyBasicTexture"));

    sf::Sprite enemyAdvanced;
    enemyAdvanced.setTexture(resourceManager.getTexture("enemyAdvancedTexture"));

    sf::Sprite enemyElite;
    enemyElite.setTexture(resourceManager.getTexture("enemyEliteTexture"));

    sf::Sprite space;
    space.setTexture(resourceManager.getTexture("space"));
    

    sf::Texture texture;
    texture = resourceManager.getTexture("foregroundTexture");
    sf::Sprite foregroundTexture;
    foregroundTexture.setTexture(resourceManager.getTexture("foregroundTexture"));
    sf::Sprite foreground1(foregroundTexture);
    sf::Sprite foreground2(foregroundTexture);
    foreground1.setColor(sf::Color(255, 255, 255, 100));
    foreground2.setColor(sf::Color(255, 255, 255, 100));
    float foregroundScaleFactor = 0.8f;

    float scaleX = static_cast<float>(window.getSize().x) / frames[0].getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / frames[0].getSize().y;
    float scaleXfore = static_cast<float>(window.getSize().x) / texture.getSize().x * foregroundScaleFactor;
    float scaleYfore = scaleXfore; // Garder le ratio d'aspect pour �viter l'�tirement

    background1.setScale(scaleX, scaleY);
    background2.setScale(scaleX, scaleY);
    space.setScale(scaleX, scaleY);
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

    sf::Text name;
    name.setFont(font);
    name.setString("Intergalactic");
    name.setCharacterSize(75);
    //name.setFillColor(sf::Color::Blue);
    name.setPosition(50, 50);

    sf::Text name1;
    name1.setFont(font);
    name1.setString("Conflict");
    name1.setCharacterSize(75);
    //name1.setFillColor(sf::Color::Red);
    name1.setPosition(150, 150);

    sf::Text play;
    play.setFont(font);
    play.setString("Play");
    play.setCharacterSize(50);
    play.setFillColor(sf::Color::Red);
    play.setPosition(100, 350);
    sf::FloatRect playTextBounds = play.getGlobalBounds();
    sf::RectangleShape playHitbox(sf::Vector2f(playTextBounds.width + ESPACEMENT, playTextBounds.height + ESPACEMENT));
    playHitbox.setPosition(playTextBounds.left - 12.5f, playTextBounds.top - 12.5f);
    playHitbox.setFillColor(sf::Color::Transparent);
    playHitbox.setOutlineColor(sf::Color::Red);
    playHitbox.setOutlineThickness(1);

    sf::Text exit;
    exit.setFont(font);
    exit.setString("Exit");
    exit.setCharacterSize(50);
    exit.setFillColor(sf::Color::Red);
    exit.setPosition(250, 550);
    sf::FloatRect exitTextBounds = exit.getGlobalBounds();
    sf::RectangleShape exitHitbox(sf::Vector2f(exitTextBounds.width + ESPACEMENT, exitTextBounds.height + ESPACEMENT));
    exitHitbox.setPosition(exitTextBounds.left - 12.5f, exitTextBounds.top - 12.5f);
    exitHitbox.setFillColor(sf::Color::Transparent);
    exitHitbox.setOutlineColor(sf::Color::Red);
    exitHitbox.setOutlineThickness(1);

    sf::Text settings;
    settings.setFont(font);
    settings.setString("Settings");
    settings.setCharacterSize(50);
    settings.setFillColor(sf::Color::Red);
    settings.setPosition(50, 450);
    sf::FloatRect settingsTextBounds = settings.getGlobalBounds();
    sf::RectangleShape settingsHitbox(sf::Vector2f(settingsTextBounds.width + ESPACEMENT, settingsTextBounds.height + ESPACEMENT));
    settingsHitbox.setPosition(settingsTextBounds.left - 12.5f, settingsTextBounds.top - 12.5f);
    settingsHitbox.setFillColor(sf::Color::Transparent);
    settingsHitbox.setOutlineColor(sf::Color::Red);
    settingsHitbox.setOutlineThickness(1);

    sf::Text editor;
    editor.setFont(font);
    editor.setString("Editor");
    editor.setCharacterSize(50);
    editor.setFillColor(sf::Color::Red);
    editor.setPosition(350, 350);
    sf::FloatRect editorTextBounds = editor.getGlobalBounds();
    sf::RectangleShape editorHitbox(sf::Vector2f(editorTextBounds.width + ESPACEMENT, editorTextBounds.height + ESPACEMENT));
    editorHitbox.setPosition(editorTextBounds.left - 12.5f, editorTextBounds.top - 12.5f);
    editorHitbox.setFillColor(sf::Color::Transparent);
    editorHitbox.setOutlineColor(sf::Color::Red);
    editorHitbox.setOutlineThickness(1);

    sf::Text level;
    level.setFont(font);
    level.setString("Level");
    level.setCharacterSize(50);
    level.setFillColor(sf::Color::Red);
    level.setPosition(375, 450);
    sf::FloatRect levelTextBounds = level.getGlobalBounds();
    sf::RectangleShape levelHitbox(sf::Vector2f(levelTextBounds.width + ESPACEMENT, levelTextBounds.height + ESPACEMENT));
    levelHitbox.setPosition(levelTextBounds.left - 12.5f, levelTextBounds.top - 12.5f);
    levelHitbox.setFillColor(sf::Color::Transparent);
    levelHitbox.setOutlineColor(sf::Color::Red);
    levelHitbox.setOutlineThickness(1);

    std::cout << "Voici les inputs :\nZ pour aller vers le haut\nS pour aller vers le bas\nQ pour aller vers la gauche\nD pour aller vers la droite\nEspace pour tirer des missiles\nEchap pour quitter la partie\n";

    while (window.isOpen()) {
        sf::Event event;
        window.display();
        while (window.pollEvent(event)) {
            window.clear();
            window.draw(space);
            bool onPlay = false;
            bool onSettings = false;
            bool onLevel = false;
            bool onEditor = false;
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (sf::Mouse::getPosition(window).x > playHitbox.getPosition().x && sf::Mouse::getPosition(window).x < playHitbox.getPosition().x + playTextBounds.width + ESPACEMENT && sf::Mouse::getPosition(window).y > playHitbox.getPosition().y && sf::Mouse::getPosition(window).y < playHitbox.getPosition().y + playTextBounds.height + ESPACEMENT) {
                window.draw(playHitbox);
                onPlay = true;
            }

            else if (sf::Mouse::getPosition(window).x > settingsHitbox.getPosition().x && sf::Mouse::getPosition(window).x < settingsHitbox.getPosition().x + settingsTextBounds.width + ESPACEMENT && sf::Mouse::getPosition(window).y > settingsHitbox.getPosition().y && sf::Mouse::getPosition(window).y < settingsHitbox.getPosition().y + settingsTextBounds.height + ESPACEMENT) {
                window.draw(settingsHitbox);
                onSettings = true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && onSettings) {
                    std::cout << "Settings\n";
                }
            }

            else if (sf::Mouse::getPosition(window).x > levelHitbox.getPosition().x && sf::Mouse::getPosition(window).x < levelHitbox.getPosition().x + levelTextBounds.width + ESPACEMENT && sf::Mouse::getPosition(window).y > levelHitbox.getPosition().y && sf::Mouse::getPosition(window).y < levelHitbox.getPosition().y + levelTextBounds.height + ESPACEMENT) {
                window.draw(levelHitbox);
                onLevel = true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && onLevel) {
                    std::cout << "Level\n";
                }
            }

            else if (sf::Mouse::getPosition(window).x > editorHitbox.getPosition().x && sf::Mouse::getPosition(window).x < editorHitbox.getPosition().x + editorTextBounds.width + ESPACEMENT && sf::Mouse::getPosition(window).y > editorHitbox.getPosition().y && sf::Mouse::getPosition(window).y < editorHitbox.getPosition().y + editorTextBounds.height + ESPACEMENT) {
                window.draw(editorHitbox);
                onEditor = true;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && onEditor) {
                    std::cout << "Editor\n";
                }
            }

            else if (sf::Mouse::getPosition(window).x > exitHitbox.getPosition().x && sf::Mouse::getPosition(window).x < exitHitbox.getPosition().x + exitTextBounds.width + ESPACEMENT && sf::Mouse::getPosition(window).y > exitHitbox.getPosition().y && sf::Mouse::getPosition(window).y < exitHitbox.getPosition().y + exitTextBounds.height + ESPACEMENT) {
                window.draw(exitHitbox);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    window.close();
                }
            }

            else {
                onPlay = false;
                onSettings = false;
                onLevel = false;
            }
            window.draw(exit);
            window.draw(play);
            window.draw(level);
            window.draw(settings);
            window.draw(editor);
            window.draw(name);
            window.draw(name1);
            window.display();
            if (onPlay == true && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                bool game = true;
                while (game) {
                    sf::Event event;
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            window.close();
                        }
                        if (event.key.code == Keyboard::Escape) {
                            game = false;
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
            }
        }
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

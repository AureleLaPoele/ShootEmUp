#include "include/main.h"

void HandleInput(Sprite& sprite, float speed);

int main() {
    // Création window
    RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "Title");
    // V-sync
    window.setVerticalSyncEnabled(true);

    Texture texture;
    if (!texture.loadFromFile("Player_ship_v1.png")) {
        return -1;
    }

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(500, 200);

    // Define movement speed
    const float speed = 5.0f;

    // Boucle qui tourne tant que window est ouvert
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }

        // Handle continuous input
        HandleInput(sprite, speed);

        // Render
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}

void HandleInput(Sprite& sprite, float speed) {
    // Movement vectors
    float dx = 0.0f;
    float dy = 0.0f;

    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        dy -= speed;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        dy += speed;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        dx -= speed;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
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

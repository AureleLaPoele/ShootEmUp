#include "include/main.h"
// j aimelabite
void InputHandler(Event event, RenderWindow& window, Sprite& sprite);

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

	// Boucle qui tourne tant que window est ouvert
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			InputHandler(event, window, sprite);
		}
		window.clear();
		window.draw(sprite);
		window.display();
	}
	return 0;
}

void InputHandler(Event event, RenderWindow &window, Sprite& sprite) {
	if (event.type == Event::Closed) {
		window.close();
	}
	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::Escape)
			window.close();
		if (event.key.code == Keyboard::Down)
			sprite.move(0, 10);
		if (event.key.code == Keyboard::Up)
			sprite.move(0, -10);
		if (event.key.code == Keyboard::Left)
			sprite.move(-10, 0);
		if (event.key.code == Keyboard::Right)
			sprite.move(10, 0);
	}
}
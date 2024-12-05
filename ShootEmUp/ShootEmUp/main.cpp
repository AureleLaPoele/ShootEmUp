#include "include/main.h"

void InputHandler(Event event, RenderWindow& window);

int main() {
	// Création window
	RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "Title");
	// V-sync
	window.setVerticalSyncEnabled(true);

	// Boucle qui tourne tant que window est ouvert
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			InputHandler(event, window);
		}
	}
	return 0;
}

void InputHandler(Event event, RenderWindow &window) {
	if (event.type == Event::Closed) {
		window.close();
	}
	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::Escape)
			window.close();
	}
}
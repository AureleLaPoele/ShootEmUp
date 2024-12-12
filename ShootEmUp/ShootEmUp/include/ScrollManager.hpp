#ifndef SCROLL_MANAGER_HPP
#define SCROLL_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class ScrollManager {
public:
	ScrollManager(float scrollSpeed, const sf::Vector2u& windowSize);

	void addLayer(const std::vector<sf::Texture>& textures, float scale, float layerSpeed = 1.0f);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

private:
	struct Layer {
		std::vector<sf::Sprite> sprites;
		float speed;
	};

	std::vector<Layer> layers;
	float baseScrollSpeed;
	sf::Vector2u windowSize;
};

#endif

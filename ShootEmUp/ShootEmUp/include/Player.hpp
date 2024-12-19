#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "SFML/Graphics.hpp"
#include "ProjectileManager.hpp"
#include "Ship.hpp"
#include "main.hpp"

class Player : public Ship {
public:
	sf::Sprite playerShip;
	Player();

	int loadTexture();
	void move(const std::unordered_map<sf::Keyboard::Key, bool>& keyStates, float speed, const sf::RenderWindow& window);
	void shot(ProjectileManager& projectileManager, const std::unordered_map<sf::Keyboard::Key, bool>& keyStates);
};
#endif
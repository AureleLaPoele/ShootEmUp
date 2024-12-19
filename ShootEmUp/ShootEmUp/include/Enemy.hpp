#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "SFML/Graphics.hpp"
#include "Ship.hpp"
#include "main.hpp"

class Enemy : public Ship {
public:
	sf::Sprite enemyShipBasic;
	Enemy();

	int loadTextureBasic();
	void level1();
	void move(const sf::RenderWindow& window, int cycle);
	void shot(ProjectileManager& projectileManager);
};
#endif

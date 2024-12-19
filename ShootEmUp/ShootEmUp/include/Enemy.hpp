#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "SFML/Graphics.hpp"
#include "../include/ResourceManager.hpp"
#include "Ship.hpp"
#include "main.hpp"

class Enemy : public Ship {
public:
	sf::Sprite enemyShipBasic;
	sf::Sprite enemyShipAdvanced;
	sf::Sprite enemyShipBoss;
	Enemy();

	int loadTextureBasic();
	int loadTextureAdvanced();
	int loadTextureBoss();
	void level1();
	void level2();
	void level3();
	void move(const sf::RenderWindow& window, int cycle);
	void shot(ProjectileManager& projectileManager);
	bool isTouch(ProjectileManager& projectileManager, sf::Sprite player);
};
#endif

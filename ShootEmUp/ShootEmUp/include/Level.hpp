#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "Player.hpp"
#include "Enemy.hpp"

class Level {
public:
	int level;
	Player player;
	Enemy enemy;
	std::vector<Enemy> arr;

	Level() {
		player.loadTexture();
		enemy.loadTextureBasic();

	}

	void changeLevel();
	bool isFinish();
};

#endif
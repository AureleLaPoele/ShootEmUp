#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "Player.hpp"
#include "Enemy.hpp"

class Level {
public:
	int level;
	Player player;
	std::vector<Enemy> arr;

	Level() {
		player.loadTexture();
	}

	void changeLevel(int num);
	bool isFinish();
};

#endif
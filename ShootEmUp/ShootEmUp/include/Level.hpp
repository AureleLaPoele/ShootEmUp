#ifndef LEVEL_HPP
#define LEVEL_HPP
#include "Player.hpp"
#include "Enemy.hpp"

class Level {
public:
	int level;
	Player player;
	Enemy enemyBasic0;
	bool isHiddenBasic0;
	Enemy enemyBasic1;
	bool isHiddenBasic1;
	Enemy enemyBasic2;
	bool isHiddenBasic2;
	Enemy enemyBasic3;
	bool isHiddenBasic3;
	Enemy enemyBasic4;
	bool isHiddenBasic4;
	Enemy enemyBasic5;
	bool isHiddenBasic5;

	Enemy enemyAdvanced0;
	bool isHiddenAdvanced0;
	Enemy enemyAdvanced1;
	bool isHiddenAdvanced1;
	Enemy enemyAdvanced2;
	bool isHiddenAdvanced2;
	Enemy enemyAdvanced3;
	bool isHiddenAdvanced3;
	Enemy enemyAdvanced4;
	bool isHiddenAdvanced4;
	Enemy enemyAdvanced5;
	bool isHiddenAdvanced5;

	Level() {
		player.loadTexture();
		enemyBasic0.loadTextureBasic(75, 30);
		enemyBasic1.loadTextureBasic(150, 30);
		enemyBasic2.loadTextureBasic(225, 30);
		enemyBasic3.loadTextureBasic(300, 30);
		enemyBasic4.loadTextureBasic(375, 30);
		enemyBasic5.loadTextureBasic(450, 30);
		isHiddenBasic0 = false;
		isHiddenBasic1 = false;
		isHiddenBasic2 = false;
		isHiddenBasic3 = false;
		isHiddenBasic4 = false;
		isHiddenBasic5 = false;

		enemyAdvanced0.loadTextureAdvanced(75, 30);
		enemyAdvanced1.loadTextureAdvanced(150, 30);
		enemyAdvanced2.loadTextureAdvanced(225, 30);
		enemyAdvanced3.loadTextureAdvanced(300, 30);
		enemyAdvanced4.loadTextureAdvanced(375, 30);
		enemyAdvanced5.loadTextureAdvanced(450, 30);
		isHiddenAdvanced0 = false;
		isHiddenAdvanced1 = false;
		isHiddenAdvanced2 = false;
		isHiddenAdvanced3 = false;
		isHiddenAdvanced4 = false;
		isHiddenAdvanced5 = false;
	}

	void changeLevel(int num);
	bool isFinish();
};

#endif
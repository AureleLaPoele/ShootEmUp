#include "../include/player.h"

Player::Player(int hp) : hp(hp) {}

bool Player::isAlive() const {
	return hp > 0;
}

void Player::mov(int add_x, int add_y, int direction_x, int direction_y) {
	bool exit = false;
	while (!exit) {
		
	}
}
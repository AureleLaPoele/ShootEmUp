#include "../include/Ship.hpp"

Ship::Ship(int hp) : hp(hp) {}

bool Ship::isAlive() const {
	return hp > 0;
}
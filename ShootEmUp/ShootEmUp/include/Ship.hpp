#ifndef SHIP_HPP
#define SHIP_HPP
#include <SFML/Graphics.hpp>
#include "main.hpp"

class Ship {
public:
	int hp;
	int x, y;

	Ship(int hp);
	virtual ~Ship() = default;
	
	bool isAlive() const;
};

#endif

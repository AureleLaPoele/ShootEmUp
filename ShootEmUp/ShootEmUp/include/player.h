#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
	int hp;
	RectangleShape j1;

	Player(int hp);
	
	virtual void mov(int add_x, int add_y, int direction_x, int direction_y);
	bool isAlive() const;
};
#endif

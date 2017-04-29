#pragma once
#include "Player.h"
/*
This is a generic class
This is just an abstraction.
It's literally the player class. I needed to add nothing more
*/
class MovableWall : public Player
{
public:
	MovableWall(int x, int y, int w, int h);
	~MovableWall();
};


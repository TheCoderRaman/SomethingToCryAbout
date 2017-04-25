#pragma once
#include "Player.h"
#include <time.h>
class GenericActor : public Player
{
public:
	GenericActor();
	GenericActor(int x, int y, int w, int h, int ida)
	{
		_x = x;
		_y = y;
		_w = w;
		_h = h;
		id = ida;

		rect.x = _x;
		rect.y = _y;
		rect.w = _w;
		rect.h = _h;

	}
	void AI_Loop()
	{
		srand(time(0) * id - 250 + id);
		int moveX = rand() % 2+1;
		int moveY = rand()%2+1;
		if (moveX == 1){
			_x -= 16.0f / 250;
			_angle = -90;
		}
		if (moveX == 2)
		{
			_x += 16.0f / 250;
			_angle = 90;
		}
		if (moveY == 1)
		{
			_y += 16.0f / 250;
			_angle = 180;
		}
		if (moveY == 2)
		{
			_y -= 16.0f / 250;
			_angle = 0;
		}
	}
	int id;
private:

};


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
	~GenericActor();
	virtual void AI_Loop();
	int id;
private:
};


#include "MovableWall.h"


MovableWall::MovableWall(int x, int y, int w, int h)
{
	_x = x;
	_y = y;
	_w = w;
	_h = h;
	rect.x = _x;
	rect.y = _y;
	rect.w = _w;
	rect.h = _h;
}


MovableWall::~MovableWall()
{
	texture.FreeResources();
}

#include "Wall.h"

Wall::Wall(int x, int y, int w, int h, bool breakable) :
_x{ x }, _y{ y }, _w{ w }, _h{ h }
{
}


Wall::~Wall()
{
}

void Wall::Draw(SDL_Renderer **render, float x, float y)
{
	rect.x = _x - x;
	rect.y = _y - y;
	rect.w = _w;
	rect.h = _h;
	SDL_RenderCopy(*render, texture.getTexture(), NULL, &rect);
}

#include "Wall.h"

Wall::Wall(int x, int y, int w, int h, bool breakable) :
_x{ x }, _y{ y }, _w{ w }, _h{ h }
{
}


Wall::~Wall()
{
}

void Wall::Draw(SDL_Renderer **render)
{
	rect.x = _x;
	rect.y = _y;
	rect.w = _w;
	rect.h = _h;
	SDL_RenderCopy(*render, texture.getTexture(), NULL, &rect);
}

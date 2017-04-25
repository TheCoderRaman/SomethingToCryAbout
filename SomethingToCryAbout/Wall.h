#pragma once
#include <SDL.h>
#include <string>
#include "Sprite.h"
// Pretty much a glorified sprite at this point.
class Wall : public Sprite
{
public:
	Wall(int x, int y, int w, int h);
	~Wall();
	void Draw(SDL_Renderer **render);;
private:
	int _x, _y, _w, _h;
};


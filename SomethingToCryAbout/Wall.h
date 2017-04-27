#pragma once
#include <SDL.h>
#include <string>
#include "Sprite.h"
// Pretty much a glorified sprite at this point.
class Wall : public Sprite
{
public:
	Wall(int x, int y, int w, int h, bool breakable);
	~Wall();
	void Draw(SDL_Renderer **render);
	bool IsBreakable() { return breakable;  }
private:
	int _x, _y, _w, _h;
	bool breakable = false;
};


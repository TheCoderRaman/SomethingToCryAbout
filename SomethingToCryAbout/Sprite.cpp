#include "Sprite.h"


/*
The Constructor
Provide X and Y ( which may change )
The Width and Height however are as they are.
*/
/*
====================
Return Type : void
FlatDraw(Renderer, 2dVector Coords)
--------------------------
Description
=======================
This function draws the sprite without being displaced by Camera Coordinates
*/
void Sprite::FlatDraw(SDL_Renderer** render, float x, float y)
{
	_x = x;
	_y = y;
	rect.x = _x;
	rect.y = _y;
	SDL_RenderCopy(*render, texture.getTexture(), NULL, &rect);
}
Sprite::Sprite(int x, int y, int w, int h, int type)
{
	_x = x;
	_y = y;
	_w = w;
	_h = h;
	rect.x = _x;
	rect.y = _y;
	rect.h = _h;
	rect.w = _w;
	TYPE = type;
}

Sprite::Sprite(int x, int y, int w, int h)
{
	_x = x;
	_y = y;
	_w = w;
	_h = h;
	rect.x = _x;
	rect.y = _y;
	rect.h = _h;
	rect.w = _w;
}
/*
Wrapper Function
Calls LoadFromFile of it's internal Texture class
*/
void Sprite::LoadTexture(char* location, SDL_Renderer &render)
{
	texture.LoadFromFile(location, &render);
	loaded = true;
}

// Destructor
Sprite::~Sprite()
{
	texture.FreeResources();
}
/*
Simple Draw To The Screen.
Like any other draw function I suppose.
*/
void Sprite::Draw(float x, float y, SDL_Renderer **render)
{
	rect.x = _x - x;
	rect.y = _y - y;
	SDL_RenderCopy(*render, texture.getTexture(), NULL, &rect);
}

void Sprite::DrawNoCoords(SDL_Renderer **render)
{
	SDL_RenderCopy(*render, texture.getTexture(), NULL, &rect);
}
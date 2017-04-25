#include "Sprite.h"


/*
The Constructor
Provide X and Y ( which may change )
The Width and Height however are as they are.
*/
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
void Sprite::Draw(int x, int y, SDL_Renderer **render)
{
	rect.x = x;
	rect.y = y;
	SDL_RenderCopy(*render, texture.getTexture(), NULL, &rect);
}

void Sprite::DrawNoCoords(SDL_Renderer **render)
{
	SDL_RenderCopy(*render, texture.getTexture(), NULL, &rect);
}
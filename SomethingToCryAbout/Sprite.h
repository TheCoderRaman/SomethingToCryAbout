#pragma once
#include "Texture.h"
/*
 Class Sprite

 A very basic Sprite Class
 To be used as the base for any other class that can be drawn with a texture.
 Has the bare essential functions
*/
class Sprite
{
public:
	Sprite(){}
	Sprite(int x, int y, int w, int h);
	~Sprite();
	virtual void Draw(int x, int y, SDL_Renderer **render); // Using coordinates
	void DrawNoCoords(SDL_Renderer **render); // ALT OPTION
	void LoadTexture(char* location, SDL_Renderer &render);
	SDL_Rect rect;
protected:
	Texture texture;
	int _x, _y, _w, _h;
};


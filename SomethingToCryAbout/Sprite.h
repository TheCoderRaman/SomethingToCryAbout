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
	Sprite(int x, int y, int w, int h, int type);
	Sprite(int x, int y, int w, int h);
	~Sprite();
	// CHANGED TO WORK WITH A CAMERA

	virtual void Draw(float x, float y, SDL_Renderer **render); // Using coordinates
	void DrawNoCoords(SDL_Renderer **render); // ALT OPTION
	void LoadTexture(char* location, SDL_Renderer &render);
	void SetRectWidth(int x)
	{
		rect.w = x;
	}
	void DrawRect(int x, int y, int r, int g, int b, SDL_Renderer** render){
		rect.x = _x - x;
		rect.y = _y - y;
		SDL_SetRenderDrawColor(*render, r, g, b, 1.0f);
		//SDL_Render(*render, &rect);
		SDL_RenderFillRect(*render, &rect);
	}
	virtual void FlatDraw(SDL_Renderer** render, float x, float y); // Also known as UI Drawing as it ignores the Camera completely :D
	bool TextureIsLoaded() { return loaded; }
	SDL_Rect rect;
	float _angle;
	int TYPE;
protected:
	Texture texture;
	
	bool loaded = false;
	float _x, _y, _w, _h;
};


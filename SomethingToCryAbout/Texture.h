#pragma once
#include "common.h"
#define _SDL_IMG

// This is a utility class
// Please do not use seperately.
class Texture
{
public:
	Texture();
	~Texture();
	SDL_Texture *getTexture();
	// Self Rendering
	void Render(int x, int y, int w, int h, int angle, SDL_Renderer *render)
	{
		SDL_Rect self{x, y, w, h};
		SDL_Point * cetner = NULL;
		SDL_RenderCopyEx(render, m_texture, NULL, &self, angle, cetner, SDL_FLIP_NONE);
	}
	void RenderToWholeScreen(SDL_Renderer* render)
	{
		SDL_Rect self{ 0, 0, 800, 600 };
		SDL_RenderCopy(render, m_texture, NULL, &self);
	}
	void FreeResources()
	{
		SDL_DestroyTexture(m_texture);
	}
	bool LoadFromFile(char* location, SDL_Renderer* render);
private:
	SDL_Texture* m_texture = nullptr;
};


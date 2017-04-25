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
	void FreeResources()
	{
		SDL_DestroyTexture(m_texture);
	}
	bool LoadFromFile(char* location, SDL_Renderer* render);
private:
	SDL_Texture* m_texture = nullptr;
};


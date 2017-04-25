#include "Texture.h"


Texture::Texture()
{
}


Texture::~Texture()
{
//	if ( m_texture != 0 )
//	SDL_DestroyTexture(m_texture);
}

SDL_Texture *Texture::getTexture()
{
	return m_texture;
}

bool Texture::LoadFromFile(char* location, SDL_Renderer* render)
{
	SDL_Surface* tmp;
	tmp = IMG_Load(location);
	m_texture = SDL_CreateTextureFromSurface(render, tmp);
	SDL_FreeSurface(tmp);
	return true;
}
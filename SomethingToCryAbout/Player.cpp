#include "Player.h"

void Player::Draw(SDL_Renderer **render, float x, float y)
{
	rect.x = _x - x;
	rect.y = _y - y;
	rect.w = _w;
	rect.h = _h;
	SDL_RenderCopyEx(*render, texture.getTexture(), NULL, &rect, _angle, NULL, SDL_FLIP_NONE);
	fxCoolDown--;
	if (fxCoolDown <= 0){
		fxCoolDown = 40;
		SDL_SetTextureColorMod(texture.getTexture(), 255, 255, 255);
	}
}

Player::~Player()
{
	texture.FreeResources();
}
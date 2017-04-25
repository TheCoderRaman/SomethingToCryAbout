#include "Player.h"

void Player::Draw(SDL_Renderer **render)
{
	rect.x = _x;
	rect.y = _y;
	rect.w = _w;
	rect.h = _h;
	SDL_RenderCopyEx(*render, texture.getTexture(), NULL, &rect, _angle, NULL, SDL_FLIP_NONE);
}
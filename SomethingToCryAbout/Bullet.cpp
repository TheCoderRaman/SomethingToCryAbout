#include "Bullet.h"
#include <chrono>
#include "Enemy.h"

// Lifetime is in seconds
Bullet::Bullet(int angle, float vX, float vY, int x, int y, int lifeTime, SDL_Renderer *rend):
_vX(vX), _vY(vY), _angle(angle), _lifeTime(lifeTime)
{
	_x = x;
	_y = y;
	rect.x = _x;
	rect.y = _y;
	rect.w = 25;
	rect.h = 25;
	texture.LoadFromFile("Assests\\bullet.png", rend);
}

void Bullet::CheckIfDestroyable()
{
	if (_lifeTime <= 0)
		destroy = true;
}

Bullet::~Bullet()
{
	texture.FreeResources();
}

void Bullet::Draw(SDL_Renderer** render)
{
	rect.x = _x;
	rect.y = _y;
	SDL_RenderCopyEx(*render, texture.getTexture(), NULL, &rect, _angle, NULL, SDL_FLIP_NONE);
}
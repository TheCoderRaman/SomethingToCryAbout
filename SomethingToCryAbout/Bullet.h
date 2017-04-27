#pragma once
#include "Sprite.h"
#include "Wall.h"
#include "Player.h"
class Enemy;
class Bullet : public Sprite
{
public:
	// Speed (vX) is divided by 300
	Bullet(int angle, float vX, float vY, int x, int y, int lifeTime, SDL_Renderer* rend);
	~Bullet();
	void Draw(SDL_Renderer **render);
	//Based on ticks.
	// my first official use of templates. Finally I think outside of the box
	template <class T>
	bool CheckIfTouching(T &other)
	{
		bool collideX = (other.rect.x  < rect.x + rect.w && other.rect.x + other.rect.w > rect.x);
		bool collideY = (other.rect.y  < rect.y + rect.h &&	other.rect.y + other.rect.h > rect.y);

		_vY = 1.6f / 10;
		_vY = 1.6f / 10;
		return collideX && collideY;
	}

	bool IsDestroyable() { return destroy; }
	void CheckIfDestroyable();
	void SetDestroyable(bool c)
	{
		destroy = c;
	}
	void action()
	{
		if (_angle == 90)
		_x += _vX/60;
		if (_angle == -90)
		_x -= _vX/60;
		if (_angle == 180)
		_y += _vX/60;
		if (_angle == 0)
		_y -= _vX/60;

		_lifeTime--;
	}
	void AddToX(int val)
	{
		_x += val;
	}
	bool CollisionWall(Wall &other)
	{
		bool collideX = (other.rect.x  < rect.x + rect.w && other.rect.x + other.rect.w > rect.x);
		bool collideY = (other.rect.y  < rect.y + rect.h &&	other.rect.y + other.rect.h > rect.y);

		return collideX && collideY;
	}
private:
	float _vX, _vY, _angle;
	int _lifeTime;

	bool destroy = false;
};


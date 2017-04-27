#pragma once
#include "common.h"
#include "GenericActor.h"
#include <vector>
#include "Bullet.h"
class Enemy : public GenericActor
{
public:
	Enemy();
	Enemy(int x, int y, int w, int h, int ida)
	{
		_x = x;
		_y = y;
		_w = w;
		_h = h;
		id = ida;

		rect.x = _x;
		rect.y = _y;
		rect.w = _w;
		rect.h = _h;
	}
	~Enemy();
	void Draw(SDL_Renderer **render);
	void AI_Loop(Player &player);
	bool isAggroed()  { return aggro; }
	int getSignal() { return s; }
	bool isDead(){ if (health <= 0) return true; else return false; };
	int GetCoolDown() { return firingCoolDown; }
	void TakeDamage(int val)
	{
		lfTimeFX = 10;
		health -= val;
		SDL_SetTextureColorMod(texture.getTexture(), 125, 0, 0);
		_x -= _vX;
		_y -= _vY;
	}
private:
	int lfTimeFX = 30; // Red Effect LifeTime
	int health = 400;
	bool aggro;
	bool dead;
	int s;
	int firingCoolDown = 2000;
};


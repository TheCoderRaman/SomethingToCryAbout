#pragma once
#include "Enemy.h"
/*
Sentry AI is for Sentry type enemies. Stationary and only fire if in vision.
*/
class Sentry_AI : public Enemy
{
public:
	Sentry_AI();
	Sentry_AI(int x, int y, int w, int h, int angle)
	{
		_x = x;
		_y = y;
		_w = w;
		_h = h;
		_angle = angle;
		rect.x = _x;
		rect.y = _y;
		rect.w = _w;
		rect.h = _h;
	}
	~Sentry_AI();
	void AI_Loop(Player &player, uint32_t deltaTime);
private:
	int firingCoolDown = 800;
	int firingCoolDownMax = 800;
};


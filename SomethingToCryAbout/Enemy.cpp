#include "Enemy.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	texture.FreeResources();
}

void Enemy::AI_Loop(Player &player, uint32_t deltaTime)
{
	s = 0;
	float distX = abs(player.GetX() - _x);
	float distY = abs(player.GetY() - _y);
	if (distX <= 5.0f * BLOCK_SIZE && distY <= 3.0f * BLOCK_SIZE)
	{
		aggro = true;
	}
	else
	{
		aggro = false;
	}
	// KEY
	// ANGLE 0 == UP -=
	// ANGLE 180 == DOWN +=
	// ANGLE 90 == RIGHT +=
	// ANGLE -90 == LEFT -=
	if (isAggroed() == true)
	{
		// Fight code
//		std::printf("This Enemy has been aggroed\n");
		if (distX <= 4.0f * BLOCK_SIZE && distY <= 4.0f * BLOCK_SIZE)
		{
			if (_x != player.GetX() + player.GetWidth())
			{
				if (player.GetAngle() == 90)
				{
					_x -= _vX*deltaTime;
				}
				if (player.GetAngle() == -90)
				{
					_x += _vX*deltaTime;
				}
			}
			if (_y != player.GetY() + player.GetHeight())
			{
				if (player.GetAngle() == 0){
					_y -= _vY*deltaTime;
				}
				if (player.GetAngle() == 180){
					_y += _vY*deltaTime;
				}
			}
		}
		else
		{
	//		std::printf("It's firing at you.\n");
			s = 1;
		}
		_angle = -player.GetAngle();
	}
	else
	{
		// Generic State
	//	std::printf("This Enemy is not angry.\n");
		srand(time(0) * id - 250 + id);
		int moveX = rand() % 2 + 1;
		int moveY = rand() % 2 + 1;
		if (moveX == 1){
			_x -= _vX/3*deltaTime/2;
			_angle = -90;
		}
		if (moveX == 2)
		{
			_x += _vX/3*deltaTime/2;
			_angle = 90;
		}
		if (moveY == 1)
		{
			_y += _vY/3*deltaTime/2;
			_angle = 180;
		}
		if (moveY == 2)
		{
			_y -= _vY/3*deltaTime/2;
			_angle = 0;
		}
	}
	firingCoolDown--;
	lfTimeFX--;
}

void Enemy::Draw(SDL_Renderer ** render, float x, float y)
{
	rect.x = _x - x ;
	rect.y = _y - y;
	rect.w = _w;
	rect.h = _h;
	SDL_RenderCopyEx(*render, texture.getTexture(), NULL, &rect, _angle, NULL, SDL_FLIP_NONE);
	if (lfTimeFX == 0)
		SDL_SetTextureColorMod(texture.getTexture(), 255, 255, 255);
	if (firingCoolDown == 0)
		firingCoolDown = firingCoolDownMax;
}
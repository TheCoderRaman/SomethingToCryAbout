#pragma once
#include "Sprite.h"
// Also entity
#include <stdio.h>
#include "Wall.h"

class Player :
	public Sprite
{
public:
	Player(){}
	Player(int x, int y, int w, int h)
	{
		_x = x;
		_y = y;
		_w = w;
		_h = h;

		rect.x = _x;
		rect.y = _y;
		rect.w = _w;
		rect.h = _h;
		
	}
	void Draw(SDL_Renderer **render);
	void Collision(Player &other)
	{
		// Reimplement later
	}// Prototype Function for now
	int flag;
	bool DeathCheck()
	{
		if (_health <= 0)
		{
			return true;
		}
		else
		{
			false;
		}
	}
	bool CheckIfTouching(Wall &other)
	{
		bool collideX = (other.rect.x  < rect.x + rect.w && other.rect.x + other.rect.w > rect.x);
		bool collideY = (other.rect.y  < rect.y + rect.h &&	other.rect.y + other.rect.h > rect.y);

		_vY = 1.6f / 30;
		_vY = 1.6f / 30;
		return collideX && collideY;
	}
	void SetPosition(int x, int y)
	{
		_x = x;
		_y = y;
	}
	void CWallCollision(Wall &other)
	{
		{
			bool collideX = (other.rect.x  < rect.x + rect.w && other.rect.x + other.rect.w > rect.x);
			bool collideY = (other.rect.y  < rect.y + rect.h &&	other.rect.y + other.rect.h > rect.y);
			// Memorize this. Or at least know what it means
			int pRight = rect.x + rect.w;
			int pBottom = rect.y + rect.h;
			int oRight = other.rect.x + other.rect.w;
			int oBottom = other.rect.y + other.rect.h;

			int t_collision = pBottom - other.rect.y;
			int b_collision = oBottom - rect.y;
			int l_collision = pRight - other.rect.x;
			int r_collision = oRight - rect.x;
			int prevX = _x;
			int prevY = _y;
			if (CheckIfTouching(other)){
				if (t_collision < b_collision && t_collision < l_collision && t_collision < r_collision)
				{
					//Top collision
					_y = prevY;
				}
				if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
				{
					//bottom collision
					_y = other.rect.y + other.rect.h;
				}
				if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
				{
					//Left collision
					_x = prevX;
				}
				if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision)
				{
					//Right collision
					_x = other.rect.x + other.rect.w;
				}
			}
		}
	}


	float _x, _y;
	float _vX = 1.6 / 20;
	float _vY = 1.6 / 20;
	int _w, _h;
	int _health = 100;
	int _angle;

};


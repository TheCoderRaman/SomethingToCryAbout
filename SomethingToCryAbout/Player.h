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
	Player(const int x, const int y, const int w, const int h)
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
	~Player();
	void Draw(SDL_Renderer **render, float x, float y);
	void Collision(const Player &other)
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
			return false;
		}
	}
	float GetX() { return _x; }
	float GetY() { return _y; }
	float GetWidth() { return _w; }
	float GetHeight() { return _h; }
	float GetAngle() { return _angle; }
	void TakeDamage(float val)
	{
		_health -= val;
		if (fxCoolDown == 40)
		SDL_SetTextureColorMod(texture.getTexture(), 127, 10, 10);
	}
	template <class T>
	bool CheckIfTouching(const T &other)
	{
		bool collideX = (other.rect.x  < rect.x + rect.w && other.rect.x + other.rect.w > rect.x);
		bool collideY = (other.rect.y  < rect.y + rect.h &&	other.rect.y + other.rect.h > rect.y);

		_vY = 1.6f / 10;
		_vY = 1.6f / 10;
		return collideX && collideY;
	}
	void SetPosition(const int x, const int y)
	{
		_x = x;
		_y = y;
	}
	template <class T>
	void CWallCollision(const T &other, float x, float y)
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
			float prevX = _x;
			float prevY = _y;
			if (CheckIfTouching<T>(other)){
				if (t_collision <= b_collision && t_collision <= l_collision && t_collision <= r_collision)
				{
					//Top collision
					std::printf("Top Collision\n");
					_y -= _vY*3;
				}
				if (b_collision <= t_collision && b_collision <= l_collision && b_collision <= r_collision)
				{
					//bottom collision
					std::printf("Bottom Collision\n");
					_y += _vY * 3;
				}
				if (l_collision <= r_collision && l_collision <= t_collision && l_collision <= b_collision)
				{
					//Left collision
					std::printf("Left Collision\n");
					_x -= _vX * 3;
				}
				if (r_collision <= l_collision && r_collision <= t_collision && r_collision <= b_collision)
				{
					//Right collision
					std::printf("Right Collision\n");
					_x += _vX*3 ;
				}
			}
		}
	}


	float _x, _y;
	float _vX = 1.6 / 10;
	float _vY = 1.6 / 10;
	int _w, _h;
	float _health = 100;
	private:
		int fxCoolDown = 40;
};


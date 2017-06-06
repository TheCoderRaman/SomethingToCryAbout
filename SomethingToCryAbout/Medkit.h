#pragma once
#include "Sprite.h"
class Medkit : public Sprite
{
public:
	Medkit(){}
	Medkit(int x, int y, int w, int h, int type)
	{
		_x = x;
		_y = y;
		_w = w;
		_h = h;
		rect.x = _x;
		rect.y = _y;
		rect.h = _h;
		rect.w = _w;
		TYPE = type;
	}
	Medkit(int x, int y, int w, int h)
	{
		_x = x;
		_y = y;
		_w = w;
		_h = h;
		rect.x = _x;
		rect.y = _y;
		rect.h = _h;
		rect.w = _w;
	}
	void SetPos(const int x, const int y)
	{
		_x = x;
		_y = y;
	}
	~Medkit(){
		texture.FreeResources();
	}
private:
};
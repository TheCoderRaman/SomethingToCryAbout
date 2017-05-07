#pragma once
#include "Sprite.h"
#include <functional>
class Button : public Sprite
{
public:
	/* Constructor 1 */
	Button(int x, int y, int w, int h, int type);
	/*Deconstructor*/
	~Button();
	virtual void Draw(int x, int y, SDL_Renderer** render) final;
	virtual void FlatDraw(SDL_Renderer** render = NULL, float x = 0, float y = 0) final;
	bool IsClickedOn(std::function<void( int )> callback, SDL_Event &e);
};


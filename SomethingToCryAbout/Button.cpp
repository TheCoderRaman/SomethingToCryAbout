#include "Button.h"
#include <cstdio>

Button::Button(int x, int y, int w, int h, int type)
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


Button::~Button()
{
}
/*
====================
Return Type : void
Draw(Renderer, 2dVector Coords)
--------------------------
Description
=======================
This function is equivalent to Sprite clases' FlatDraw function.
*/
void Button::Draw(int x, int y, SDL_Renderer** render)
{
	_x = x;
	_y = y;
	rect.x = _x;
	rect.y = _y;
	SDL_RenderCopy(*render, texture.getTexture(), NULL, &rect);
}
/*
====================
Return Type : void
FlatDraw(Renderer, 2dVector Coords)
--------------------------
Description
=======================
This function is inherited from Sprite class. It is defunct in this class
and throws an exception when used. AKA Please don't use
*/
#ifdef USE_UNUSUABLEFUNC
void Button::FlatDraw(SDL_Renderer** render, float x, float y)
{
	/*
	Please don't use this function. It's just a left over from the Sprite class
	*/
	try{
		throw 0;
	}
	catch (int exception)
	{
		std::printf("This function is not recommended. Please use the Draw method. Thank you.");
	}
}
#endif
#define PLACEHOLDER
#ifdef PLACEHOLDER
/*
====================
Return Type : void
FlatDraw(Renderer, 2dVector Coords)
--------------------------
Description
=======================
This function is inherited from Sprite class. It is defunct in this class
and throws an exception when used. AKA Please don't use
*/
void Button::FlatDraw(SDL_Renderer** render, float x, float y)
{
}
#endif
/* 
====================
	Return Type : Boolean
	IsClickedOn((void*)callbackFunc, eventStruct)
--------------------------
	Description
=======================
	This function detects whether the mouse pointer is inside of the button.
	It uses a function object to callback a Handler to call the actual callbacks
*/
bool Button::IsClickedOn(std::function<void(int)> callback, SDL_Event &e)
{
	// Let's check if we collide with the bounds
	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
		int x, y;
		bool inside = true;
		SDL_GetMouseState(&x, &y);
		if (x > rect.x + rect.w){
			printf("Mouse is Outside\n");
			inside = false;
		}
		else if (x < rect.x){
			printf("Mouse is Outside\n");
			inside = false;
		}
		if (y > rect.y + rect.h){
			printf("Mouse is Outside\n");
			inside = false;
		}
		else if (y < rect.y){
			printf("Mouse is Outside\n");
			inside = false;
		}

		if (inside == true)
		{
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				callback(TYPE); // Functional Based Code. Reduces 90% of my workload
			}
		}
		return inside;
	}
}
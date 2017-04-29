#pragma once
#include "common.h"

class Window
{
public:
	Window(Uint32 flags, int width, int height, char* name);
	~Window();
	SDL_Window *getWindow(); // for rendering purposes
	bool CreateWindow();
	void CleanUp(); // Destructor function
private:
	SDL_Window* m_window = NULL;
	int m_width;
	int m_height;
	Uint32 m_flags;
	char* m_name;

};


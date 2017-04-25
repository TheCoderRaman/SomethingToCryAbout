#pragma once
#include "common.h"

class Window
{
public:
	Window(SDL_WindowFlags flags, int width, int height, char* name);
	~Window();
	SDL_Window *getWindow(); // for rendering purposes
	bool CreateWindow();
	void CleanUp(); // Destructor function
private:
	SDL_Window* m_window = NULL;
	int m_width;
	int m_height;
	SDL_WindowFlags m_flags;
	char* m_name;

};


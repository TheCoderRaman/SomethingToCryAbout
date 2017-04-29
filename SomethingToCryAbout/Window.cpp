#include "Window.h"

// Constructor
// Flags = SDL_WINDOW FLAG
// Width = window width
// Height = window height
// Name = Window Name
//
Window::Window(Uint32 flags, int width, int height, char* name)
{
	m_flags = flags;
	m_width = width;
	m_height = height;
	m_name = name;
}


Window::~Window()
{
	CleanUp();
}
// return the window struct
SDL_Window *Window::getWindow()
{
	return m_window;
}

// A Destructor Function
void Window::CleanUp()
{
	// few other things
	SDL_DestroyWindow(m_window);
}

/*
Create a window with the settings specified
by Constructor.
*/
bool Window::CreateWindow()
{
	if ((m_window = SDL_CreateWindow(m_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, m_flags)))
		return true;
	else
		return false;
}
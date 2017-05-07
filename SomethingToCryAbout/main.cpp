// SomethingToCryAbout
//
// A Project where I put some random ideas and make a game with them.
//

#include "stdafx.h"
#include "Window.h"
#include "Game.h"
int main(int argc, char* argv[])
{
	bool fl = true;
	GameBase::Init();
	Window window(SDL_WINDOW_SHOWN, 800, 600, "Revision 2 : The Refactoring");
	window.CreateWindow();
	GameBase::RunGame(fl, &window);
	return 0;
}

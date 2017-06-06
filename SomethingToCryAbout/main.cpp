// SomethingToCryAbout
//
// A Project where I put some random ideas and make a game with them.
//

#include "stdafx.h"
#include "ConfigReader.h"
#include "Window.h"
#include "Game.h"
int main(int argc, char* argv[])
{
	bool fl = true;
	int w, h, flag;
	GameBase::Init();
	FileSystem::ParseFile("ini\\settings.ini", w, h, flag);
	Window window(SDL_WINDOW_SHOWN | flag, w, h, "Revision 2 : The Refactoring");
	window.CreateWindow();
	GameBase::RunGame(fl, &window);
	GameBase::Quit();
	return 0;
}

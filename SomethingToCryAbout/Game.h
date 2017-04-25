// Functions for the game
#include "common.h"
#include "stdafx.h"
#define EVERYTHING
#include "Window.h"
#include <vector>
#include "Level.h"
#include "GenericActor.h"
// Global Variables
// Like Buttons etc.
/*
I'm am desperately attempting to savage this if I can
For some reason all entities are players... Ughh...
*/

SDL_Event e; // For General Events
SDL_Renderer* render; // GLOBAL RENDERER
Player player(0,0, 50, 50);
std::vector<GenericActor> actors;
std::vector<Wall> walls;
std::vector<Sprite> sprites;
Level test("Assests\\levels\\test.txt");
// END OF GLOBAL VARIABLES
void CleanUp()
{
	SDL_Quit();
}

// Will require a PLAYER class in arguments as well cause, input
void ProcessInput(Window* window, bool &running, Player* player)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			window->CleanUp(); // Essentially FORCE the destructor
			CleanUp();
			running = false;
		}
	}
		if (state[SDL_SCANCODE_W])
		{
			if ( player->_y != 0 && player->_y > 0)
			player->_y -= player->_vY;
			player->_angle = 0;
		}
		if (state[SDL_SCANCODE_S])
		{
			if (player->_y != 768 && player->_y < 768)
			player->_y += player->_vY;
			player->_angle = 180;
		}
		if (state[SDL_SCANCODE_D])
		{
			player->_x += player->_vX;
			player->_angle = 90;
		}
		if (state[SDL_SCANCODE_A])
		{
			player->_x -= player->_vX;
			player->_angle = -90;
		}
}

void Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
}

/*
This is the function that controls the whole game.
Very badly organized but for my needs it's working as intended.
*/
void RunGame(bool &running, Window* window)
{
	render = SDL_CreateRenderer(window->getWindow(), 0, SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC || SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	
	test.ProcessLevel(player, walls, actors, sprites);
	for (int i = 0; i < walls.size(); i++)
		walls[i].LoadTexture("Assests\\wall.png", *render);
	for (int i = 0; i < actors.size(); i++)
		actors[i].LoadTexture("Assests\\enemy.png", *render);
	for (int i = 0; i < sprites.size(); i++)
		sprites[i].LoadTexture("Assests\\floor.png", *render);
	player.LoadTexture("Assests\\player.png", *render);
	std::printf("Walls : %d", walls.size());
	while (running == true)
	{
		// Just do game logic and crap in here
		
		ProcessInput(window, running, &player);
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderClear(render);
		for (int i = 0; i < walls.size(); i++)
		{
			walls[i].Draw(&render);
			player.CWallCollision(walls[i]);
			for (int x = 0; x < actors.size(); x++)
			actors[x].CWallCollision(walls[i]);
		}
		for (int i = 0; i < sprites.size(); i++)
		{
			sprites[i].DrawNoCoords(&render);
		}
		for (int i = 0; i < actors.size(); i++)
		{
			actors[i].Draw(&render);
			actors[i].AI_Loop();
		}
		player.Draw(&render);
		SDL_RenderPresent(render);
	}
}
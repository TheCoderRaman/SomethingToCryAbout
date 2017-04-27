// Functions for the game
#include "common.h"
#include "stdafx.h"
#define EVERYTHING
#include "Window.h"
#include <vector>
#include "Level.h"
#include <algorithm>
#include "GenericActor.h"
#include "Enemy.h"
#include "Bullet.h"
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
std::vector<Bullet> bullets;
std::vector<Bullet> enemy_bullets;
std::vector<Wall> walls;
std::vector<Enemy> enemies;
std::vector<Sprite> sprites;
bool Pressed = false; // Key Pressed
Level test("Assests\\levels\\test.txt");
// END OF GLOBAL VARIABLES
void CleanUp()
{
	actors.clear();
	bullets.clear();
	walls.clear();
	sprites.clear();
	enemies.clear();
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
		if (e.type == SDL_KEYDOWN){
			if (e.key.keysym.sym == SDLK_SPACE)
			{
				if (!Pressed){
					bullets.push_back(Bullet(player->_angle, 30, 0, player->_x + player->rect.w / 2, player->_y + player->rect.h / 2, 750, render));
					Pressed = true;
				}
			}
		}
		if (e.type == SDL_KEYUP)
		{
			Pressed = false;
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
	test.ProcessLevel(player, walls, actors, sprites, enemies);
	for (int i = 0; i < walls.size(); i++)
	{
		if (walls[i].IsBreakable() == false)
			walls[i].LoadTexture("Assests\\wall.png", *render);
	}
	for (int i = 0; i < actors.size(); i++)
		actors[i].LoadTexture("Assests\\player.png", *render);
	for (int i = 0; i < sprites.size(); i++)
		sprites[i].LoadTexture("Assests\\floor.png", *render);
	for (int i = 0; i < enemies.size(); i++)
		enemies[i].LoadTexture("Assests\\enemy.png", *render);
	player.LoadTexture("Assests\\player.png", *render);
	std::printf("Walls : %d", walls.size());
	while (running == true && player.DeathCheck() == false)
	{
		// Just do game logic and crap in here

		ProcessInput(window, running, &player);
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderClear(render);
		for (int i = 0; i < bullets.size(); i++){
			if (bullets[i].TextureIsLoaded() == false)
				bullets[i].LoadTexture("Assests\\bullet.png", *render);
		}
		for (int i = 0; i < enemy_bullets.size(); i++){
			if (enemy_bullets[i].TextureIsLoaded() == false)
				enemy_bullets[i].LoadTexture("Assests\\bullet.png", *render);
		}
		for (int i = 0; i < walls.size(); i++)
		{
			walls[i].Draw(&render);
			player.CWallCollision<Wall>(walls[i]);
			for (int x = 0; x < actors.size(); x++)
				actors[x].CWallCollision<Wall>(walls[i]);
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
		for (int i = 0; i < bullets.size(); i++)
		{
			// On the spot
			if (bullets[i].IsDestroyable() == true)
				bullets.erase(bullets.begin() + i);
			bullets[i].action();
			bullets[i].Draw(&render);
			bullets[i].CheckIfDestroyable();
			for (int j = 0; j < walls.size(); j++)
				if (bullets[i].CollisionWall(walls[j]) == true){
					bullets[i].SetDestroyable(true); // Let's avoid more crashes.
				}
			
			for (int j = 0; j < enemies.size(); j++)
			{
				if (bullets[i].CheckIfTouching<Enemy>(enemies[j])){
					enemies[j].TakeDamage(40);
					bullets[i].SetDestroyable(true);
				}
			}
		}
		for (int i = 0; i < enemy_bullets.size(); i++)
		{
			// On the spot
			if (enemy_bullets[i].IsDestroyable() == true)
				enemy_bullets.erase(enemy_bullets.begin() + i);
			enemy_bullets[i].action();
			enemy_bullets[i].Draw(&render);
			enemy_bullets[i].CheckIfDestroyable();
			for (int j = 0; j < walls.size(); j++)
				if (enemy_bullets[i].CollisionWall(walls[j]) == true){
					enemy_bullets[i].SetDestroyable(true); // Let's avoid more crashes.
				}
			if (enemy_bullets[i].CheckIfTouching<Player>(player))
			{
				player.TakeDamage(20.0f);
				enemy_bullets[i].SetDestroyable(true);
			}
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].isDead() == true)
			{
				enemy_bullets.clear(); // To avoid weird magic bullets
				enemies.erase(enemies.begin() + i);
			}
			enemies[i].Draw(&render);
			enemies[i].AI_Loop(player);
			for (int j = 0; j < walls.size(); j++)
			{
				enemies[i].CWallCollision(walls[j]);
			}
			if (enemies[i].getSignal() == 1)
			{
				if (enemies[i].GetCoolDown() > 1995)
				enemy_bullets.push_back(Bullet(enemies[i]._angle, 45, 0, enemies[i]._x + enemies[i].rect.w / 2, enemies[i]._y + enemies[i].rect.h / 2, 750, render));
			}
			enemies[i].CWallCollision<Player>(player);
			player.CWallCollision<Enemy>(enemies[i]);
		}
		player.Draw(&render);
		SDL_RenderPresent(render);
	}
}
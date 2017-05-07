// Functions for the game
#include "common.h"
#include "stdafx.h"
#define EVERYTHING
#include "Window.h"
#include <vector>
#include "Level.h"
#include <algorithm>
#include "GenericActor.h"
#include "Button.h"
#include "Enemy.h"
#include "Bullet.h"
#include "MovableWall.h"
#include "CameraStruct.h"
#include <SDL_mixer.h>
// Global Variables
// Like Buttons etc.
/*
I'm am desperately attempting to savage this if I can
For some reason all entities are players... Ughh...
*/
namespace GameBase{
	namespace GlobalVariables{
		namespace GameBools{
			bool *gRunning_ptr = nullptr;
			bool MenuActive = true;
		};
		const int w = 800;
		const int h = 600;
		const int lW = 15000;
		const int lH = 15000;
		Mix_Chunk* step, *fire;
		SDL_Event e; // For General Events
		SDL_Renderer* render; // GLOBAL RENDERER
		Player player(0, 0, 50, 50);
		Sprite health_bar(0, 450, 200, 25);
		Sprite health_meter(0, 450, 200, 10);
		namespace Vectors{
			std::vector<GenericActor> actors;
			std::vector<Bullet> bullets;
			std::vector<Bullet> enemy_bullets;
			std::vector<Wall> walls;
			std::vector<MovableWall> mWalls;
			std::vector<Enemy> enemies;
			std::vector<Sprite> sprites;
		};
		bool Pressed = false; // Key Pressed
		Level test("Assests\\levels\\collide.txt");
		namespace Clock
		{
			uint32_t last = 0;
			uint32_t delta = 0;
			void tick()
			{
				uint32_t tickTime = SDL_GetTicks();
				delta = tickTime - last;
				last = tickTime;
			}
		};
	};

	using namespace GlobalVariables;
	using namespace GlobalVariables::Vectors;

	namespace ButtonCallback{
		/*
		A Callback handler that calls callbacks. BEATUFIUL
		*/
		namespace CallBackTypes{
			void CallBack_Quit() { *GameBools::gRunning_ptr = false; }
			void CallBack_Start(){ GameBools::MenuActive = false; }
		};
		void CallBack_Handler(int type)
		{
			if (type == BUTTON_START){
				std::printf("Event :: Start Game\n");
				CallBackTypes::CallBack_Start();
			}
			if (type == BUTTON_QUIT){
				std::printf("Event :: Quit Game\n");
				CallBackTypes::CallBack_Quit();
			}
		}
	};
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
						Mix_PlayChannel(-1, fire, 0);
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
			player->_y -= player->_vY * Clock::delta;
			player->_angle = DIR_UP;
			Mix_PlayChannel(0, step, 0);
		}
		if (state[SDL_SCANCODE_S])
		{
			player->_y += player->_vY * Clock::delta;
			player->_angle = DIR_DOWN;
			Mix_PlayChannel(0, step, 0);
		}
		if (state[SDL_SCANCODE_D])
		{
			player->_x += player->_vX * Clock::delta;
			player->_angle = DIR_RIGHT;
			Mix_PlayChannel(0, step, 0);
		}
		if (state[SDL_SCANCODE_A])
		{
			player->_x -= player->_vX * Clock::delta;
			player->_angle = DIR_LEFT;
			Mix_PlayChannel(0, step, 0);
		}
	}
	void Init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG);
		Mix_Init(MIX_INIT_MP3);
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
		step = Mix_LoadWAV("Assests\\sounds\\step.wav");
		fire = Mix_LoadWAV("Assests\\sounds\\damage_hit.wav");
	}

	/*
	This is the function that controls the whole game.
	Very badly organized but for my needs it's working as intended.
	*/
	void RunGame(bool &running, Window* window)
	{
		GameBools::gRunning_ptr = &running;
		render = SDL_CreateRenderer(window->getWindow(), 0, SDL_RendererFlags::SDL_RENDERER_PRESENTVSYNC || SDL_RendererFlags::SDL_RENDERER_ACCELERATED);

		camera.camRect.w = w;
		camera.camRect.h = h;
		auto FObj_Setup = [&]() {
			// UI ELEMENTS
			Sprite banner(w / 2, h - 300, 200, 100, TYPE_UI_BANNER);
			// END OF UI
			for (int i = 0; i < walls.size(); i++)
			{
				if (walls[i].IsBreakable() == false)
					walls[i].LoadTexture("Assests\\wall.png", *render);
			}
			for (int i = 0; i < actors.size(); i++)
				actors[i].LoadTexture("Assests\\player.png", *render);
			for (int i = 0; i < sprites.size(); i++){
				if (sprites[i].TYPE == TYPE_WOOD)
					sprites[i].LoadTexture("Assests\\floor.png", *render);
				if (sprites[i].TYPE == TYPE_GRASS)
					sprites[i].LoadTexture("Assests\\grass.png", *render);
				if (sprites[i].TYPE == TYPE_METAL)
					sprites[i].LoadTexture("Assests\\metal_floor.png", *render);
			}
			for (int i = 0; i < mWalls.size(); i++)
			{
				mWalls[i].LoadTexture("Assests\\box.png", *render);
			}
			for (int i = 0; i < enemies.size(); i++)
				enemies[i].LoadTexture("Assests\\enemy.png", *render);
			player.LoadTexture("Assests\\player.png", *render);
			std::printf("Walls : %d", walls.size());
		};
		auto HUD_Setup = [&](){
			health_bar.LoadTexture("Assests\\hpBar.png", *render);
		};
		Button start(w / 2, h / 2, 300, 150, BUTTON_START);
		Button quit(w / 2, h / 2, 300, 150, BUTTON_QUIT);
		start.LoadTexture("Assests\\start.png", *render);
		quit.LoadTexture("Assests\\quit.png", *render);
		bool LevelLoaded = false;
		while (*GameBools::gRunning_ptr)
		{
			// Just do game logic and crap in here

			// camera.x = ( dot.getPosX() + Dot::DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
			// camera.y = ( dot.getPosY() + Dot::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2; 
			Clock::tick();
			ProcessInput(window, *GameBools::gRunning_ptr, &player);
			if (GameBools::MenuActive)
			{
				start.Draw(w / 2 - 230, h / 2 - 200, &render);
				quit.Draw(w / 2 - 230,  h / 2 + 140, &render);
				start.IsClickedOn(ButtonCallback::CallBack_Handler, e);
				quit.IsClickedOn(ButtonCallback::CallBack_Handler, e);
				SDL_RenderPresent(render);
			}
			else if (!GameBools::MenuActive) {
				if (LevelLoaded == false)
				{
					test.ProcessLevel(player, walls, actors, sprites, enemies, mWalls, camera.camRect.x, camera.camRect.y);
					LevelLoaded = true;
					FObj_Setup();
					HUD_Setup();
				}
				SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
				SDL_RenderClear(render);
				camera.camRect.x = (player.GetX() + player.rect.w / 2) - w / 2;
				camera.camRect.y = (player.GetY() + player.rect.h / 2) - h / 2;
				if (camera.camRect.x < 0)
				{
					camera.camRect.x = 0;
				}
				if (camera.camRect.y < 0)
				{
					camera.camRect.y = 0;
				}
				if (camera.camRect.x >= lW - camera.camRect.w)
				{
					camera.camRect.x = lW - camera.camRect.w;
				}
				if (camera.camRect.y >= lW - camera.camRect.h)
				{
					camera.camRect.y = lH - camera.camRect.h;
				}
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
					//walls[i].DrawAtOffset(camera.camRect.x, camera.camRect.y, &render);
					walls[i].Draw(&render, camera.camRect.x, camera.camRect.y);
					player.CWallCollision<Wall>(walls[i], camera.camRect.x, camera.camRect.y);
					for (int x = 0; x < actors.size(); x++)
						actors[x].CWallCollision<Wall>(walls[i], camera.camRect.x, camera.camRect.y);
					for (int j = 0; j < mWalls.size(); j++)
						mWalls[j].CWallCollision<Wall>(walls[i], camera.camRect.x, camera.camRect.y);
				}
				for (int i = 0; i < sprites.size(); i++)
				{
					sprites[i].Draw(camera.camRect.x, camera.camRect.y, &render);
				}
				for (int i = 0; i < actors.size(); i++)
				{
					actors[i].Draw(&render, camera.camRect.x, camera.camRect.y);
					actors[i].AI_Loop(Clock::delta);
				}
				for (int i = 0; i < bullets.size(); i++)
				{
					// On the spot
					if (bullets[i].IsDestroyable() == true)
						bullets.erase(bullets.begin() + i);
					bullets[i].action(Clock::delta);
					bullets[i].Draw(&render, camera.camRect.x, camera.camRect.y);
					bullets[i].CheckIfDestroyable();
					for (int j = 0; j < walls.size(); j++)
						if (bullets[i].CollisionWall(walls[j]) == true){
							bullets[i].SetDestroyable(true); // Let's avoid more crashes.
						}
					for (int j = 0; j < mWalls.size(); j++)
					{
						if (bullets[i].CheckIfTouching<MovableWall>(mWalls[j]))
						{
							bullets[i].SetDestroyable(true);
						}
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
					
					enemy_bullets[i].action(Clock::delta);
					enemy_bullets[i].Draw(&render, camera.camRect.x, camera.camRect.y);
					enemy_bullets[i].CheckIfDestroyable();
					Mix_PlayChannel(1, fire, 0);
					for (int j = 0; j < walls.size(); j++)
						if (enemy_bullets[i].CollisionWall(walls[j]) == true){
							enemy_bullets[i].SetDestroyable(true); // Let's avoid more crashes.
						}
					if (enemy_bullets[i].CheckIfTouching<Player>(player))
					{
						player.TakeDamage(25.0f / 4);
						enemy_bullets[i].SetDestroyable(true);
					}
					for (int j = 0; j < mWalls.size(); j++)
					{
						if (enemy_bullets[i].CheckIfTouching<MovableWall>(mWalls[j]))
						{
							enemy_bullets[i].SetDestroyable(true);
						}
					}
				}
				for (int i = 0; i < mWalls.size(); i++)
				{
					mWalls[i].Draw(&render, camera.camRect.x, camera.camRect.y);
					mWalls[i].CWallCollision<Player>(player, camera.camRect.x, camera.camRect.y);
					for (int x = 0; x < enemies.size(); x++)
						mWalls[i].CWallCollision<GenericActor>(enemies[x], camera.camRect.x, camera.camRect.y);
					for (int j = 0; j < mWalls.size(); j++)
						mWalls[i].CWallCollision<MovableWall>(mWalls[j], camera.camRect.x, camera.camRect.y);
				}
				for (int i = 0; i < enemies.size(); i++)
				{
					if (enemies[i].isDead() == true)
					{
						enemy_bullets.clear(); // To avoid weird magic bullets
						enemies.erase(enemies.begin() + i);
					}
					enemies[i].Draw(&render, camera.camRect.x, camera.camRect.y);
					enemies[i].AI_Loop(player, Clock::delta);
					for (int j = 0; j < walls.size(); j++)
					{
						enemies[i].CWallCollision<Wall>(walls[j], camera.camRect.x, camera.camRect.y);
					}
					if (enemies[i].getSignal() == 1)
					{
						if (enemies[i].GetCoolDown() > 1995)
							enemy_bullets.push_back(Bullet(enemies[i]._angle, 45, 0, enemies[i]._x + enemies[i].rect.w / 2, enemies[i]._y + enemies[i].rect.h / 2, 750, render));
					}
					enemies[i].CWallCollision<Player>(player, camera.camRect.x, camera.camRect.y);
					player.CWallCollision<Enemy>(enemies[i], camera.camRect.x, camera.camRect.y);
				}

				//	player.DrawAtOffset(camera.camRect.x, camera.camRect.y, &render);
				player.Draw(&render, camera.camRect.x, camera.camRect.y);
				health_bar.Draw((int)0, (int)450, &render);
				health_meter.SetRectWidth(player._health * 2);
				health_meter.DrawRect(0, 445, 255, 0, 0, & render);
				std::printf("\nCamera X %d \nCamera Y %d", camera.camRect.x, camera.camRect.y);
				std::printf("\nPlayer X %d\nPlayer Y %d", player._x, player._y);
				SDL_RenderPresent(render);
			}
			SDL_RenderPresent(render);
			if (player.DeathCheck() == true)
			{
				Sprite youdied(0, 0, w, h, TYPE_UI_BANNER);
				youdied.LoadTexture("Assests\\youdied.png", *render);
				youdied.FlatDraw(&render, 0, 0);
				SDL_RenderPresent(render);
				SDL_Delay(2000);
				return;
			}
		}
	}
};
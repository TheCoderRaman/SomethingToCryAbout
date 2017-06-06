// Use include macros for slightly less problems
#ifndef COMMON_HEADER
#define COMMON_HEADER
#include <SDL2/SDL.h>
#ifndef _SDL_MIX
#include <SDL2/SDL_mixer.h>
#endif
#ifndef _SDL_IMG
#include <SDL2/SDL_image.h>
#endif
#ifndef _SDL_TTF
#include <SDL2/SDL_ttf.h>
#endif
#ifndef EVERYTHING
#define _SDL_MIX
#define _SDL_IMG
#define _SDL_TTF
#endif
#endif
// Floor Types
#define TYPE_WOOD 0
#define TYPE_GRASS 1
#define TYPE_METAL 2
#define TYPE_MEDKIT 3
// OTHER SPRITE TYPES
#define TYPE_UI_BANNER 40
#define TYPE_UI_MENU 2000
// Sizes
#define BLOCK_SIZE 55
#define ACTOR_SIZE 50

// Directions
#define DIR_UP 0
#define DIR_DOWN 180
#define DIR_LEFT -90
#define DIR_RIGHT 90
#define DIR_UP_KEY 1
#define DIR_DOWN_KEY 2
#define DIR_LEFT_KEY 3
#define DIR_RIGHT_KEY 4
/*
	Button Defs

	I should probably use Enums for typesafe reasons
	5/7/17 likely to be last update
*/
#define BUTTON_START 101
#define BUTTON_QUIT 0
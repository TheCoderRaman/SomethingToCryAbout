// Use include macros for slightly less problems
#ifndef COMMON_HEADER
#define COMMON_HEADER
#include <SDL.h>
#ifndef _SDL_MIX
#include <SDL_mixer.h>
#endif
#ifndef _SDL_IMG
#include <SDL_image.h>
#endif
#ifndef _SDL_TTF
#include <SDL_ttf.h>
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
// OTHER SPRITE TYPES
#define TYPE_UI_BANNER 40
#define TYPE_UI_MENU 2000
// Sizes
#define BLOCK_SIZE 55
#define ACTOR_SIZE 50
#include "Sentry_AI.h"


Sentry_AI::Sentry_AI()
{
}

Sentry_AI::~Sentry_AI()
{
	texture.FreeResources();
}

void Sentry_AI::AI_Loop(Player &player, uint32_t deltaTime)
{
	s = 0;
	float distX = abs(player.GetX() - _x);
	float distY = abs(player.GetY() - _y);
	// Sentries get increased range
	if (distX <= 5.0f * BLOCK_SIZE && distY <= 5.0f * BLOCK_SIZE)
	{
		s = 1;
	}
	firingCoolDown--;
	lfTimeFX--;
}
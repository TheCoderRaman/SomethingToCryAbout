#include "GenericActor.h"


GenericActor::GenericActor()
{
}

GenericActor::~GenericActor()
{
	texture.FreeResources();
}

void GenericActor::AI_Loop()
{
		srand(time(0) * id - 250 + id);
		int moveX = rand() % 2 + 1;
		int moveY = rand() % 2 + 1;
		if (moveX == 1){
			_x -= 16.0f / 250;
			_angle = -90;
		}
		if (moveX == 2)
		{
			_x += 16.0f / 250;
			_angle = 90;
		}
		if (moveY == 1)
		{
			_y += 16.0f / 250;
			_angle = 180;
		}
		if (moveY == 2)
		{
			_y -= 16.0f / 250;
			_angle = 0;
		}
}
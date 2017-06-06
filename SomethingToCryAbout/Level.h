#pragma once
#include "Player.h"
#include "Wall.h"
#include "Enemy.h"
#include "Sentry_AI.h"
#include "Medkit.h"
#include <fstream>
#include <vector>
#include "Progressor.h"
#include "GenericActor.h"
#include "MovableWall.h"
class Level
{
public:
	Level(){}
	Level(std::string path);
	std::vector <std::string>levelData;
	void ProcessLevel(Player &player, std::vector<Wall> &walls, std::vector<GenericActor>&actors, std::vector<Sprite> &sprites, std::vector<Enemy> &enemies, std::vector<MovableWall> &mWalls, std::vector<Sentry_AI> &sentries, Progressor &pr, std::vector<Medkit>&kits , int spawnOffsetX, int spawnOffsetY);
};


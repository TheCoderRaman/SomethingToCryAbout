#pragma once
#include "Player.h"
#include "Wall.h"
#include "Enemy.h"
#include <fstream>
#include <vector>
#include "GenericActor.h"
class Level
{
public:
	Level(std::string path);
	std::vector <std::string>levelData;
	void ProcessLevel(Player &player, std::vector<Wall> &walls, std::vector<GenericActor>&actors, std::vector<Sprite> &sprites, std::vector<Enemy> &enemies);
};


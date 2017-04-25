#include "Level.h"

const int BLOCK_SIZE = 55; // no bigger than the player
const int ACTOR_SIZE = 50;
Level::Level(std::string path)
{
	std::ifstream level(path);
	if (level.good())
	{
		std::string temp;
		while (level >> temp)
		{
			levelData.push_back(temp);
		}
	}
	level.close();
}

void Level::ProcessLevel(Player &player, std::vector<Wall> &walls, std::vector<GenericActor>&actors, std::vector<Sprite> &sprites)
{
	for (int i = 0; i < levelData.size(); i++)
	{
		for (int j = 0; j < levelData[i].size(); j++)
		{
			if (levelData[i][j] == 'T')
			{
				std::printf("Actor Found!\n");
					actors.push_back(GenericActor(j*ACTOR_SIZE,i*ACTOR_SIZE, ACTOR_SIZE, ACTOR_SIZE, 2*i*j*j));
					sprites.push_back(Sprite(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
			}
			if (levelData[i][j] == '#')
			{
				std::printf("Wall found!\n");
				walls.push_back(Wall(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
			}
			if (levelData[i][j] == '@')
			{
				std::printf("Player Found!\n");
				player.SetPosition(j*ACTOR_SIZE, i*ACTOR_SIZE);
				sprites.push_back(Sprite(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
			}
			if (levelData[i][j] == '.')
			{
				std::printf("floor\n");
				sprites.push_back(Sprite(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
			}
		}
	}
}
#include "Level.h"

#include "common.h"
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

void Level::ProcessLevel(Player &player, std::vector<Wall> &walls, std::vector<GenericActor>&actors, std::vector<Sprite> &sprites, std::vector<Enemy> &enemies, std::vector<MovableWall> &mWalls, std::vector<Sentry_AI> &sentries, Progressor &pr, int spawnOffsetX, int spawnOffsetY)
{
	for (int i = 0; i < levelData.size(); i++)
	{
		for (int j = 0; j < levelData[i].size(); j++)
		{
			if (levelData[i][j] == '@')
			{
				std::printf("Player Found!\n");
				player.SetPosition(j * ACTOR_SIZE, i * ACTOR_SIZE);
				sprites.push_back(Sprite(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TYPE_WOOD));
			}
			
			if (levelData[i][j] == '1')
			{
				sentries.push_back(Sentry_AI(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, DIR_UP));
				sprites.push_back(Sprite(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TYPE_METAL));
			}
			if (levelData[i][j] == '2')
			{
				sentries.push_back(Sentry_AI(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, DIR_DOWN));
				sprites.push_back(Sprite(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TYPE_METAL));
			}
			if (levelData[i][j] == '3')
			{
				sentries.push_back(Sentry_AI(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, DIR_LEFT));
				sprites.push_back(Sprite(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TYPE_METAL));
			}
			if (levelData[i][j] == '4')
			{
				sentries.push_back(Sentry_AI(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, DIR_RIGHT));
				sprites.push_back(Sprite(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TYPE_METAL));
			}
			if (levelData[i][j] == 'E')
			{
				// Enemy
				std::printf("Enemy\n");
				enemies.push_back(Enemy(j*ACTOR_SIZE, i*ACTOR_SIZE, ACTOR_SIZE, ACTOR_SIZE, 4 * i*j - j));
				sprites.push_back(Sprite(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TYPE_WOOD));
			}
			if (levelData[i][j] == 'T')
			{
				std::printf("Actor Found!\n");
				actors.push_back(GenericActor(j*ACTOR_SIZE, i*ACTOR_SIZE, ACTOR_SIZE, ACTOR_SIZE, 2 * i*j*j));
				sprites.push_back(Sprite(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TYPE_WOOD));
			}
			if (levelData[i][j] == '#')
			{
				std::printf("Wall found!\n");
				walls.push_back(Wall(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, false));
			}
			if (levelData[i][j] == ',')
			{
				sprites.push_back(Sprite(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TYPE_GRASS));
			}
			if (levelData[i][j] == ':')
			{
				sprites.push_back(Sprite(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TYPE_METAL));
			}
			if (levelData[i][j] == '.')
			{
				std::printf("floor\n");
				sprites.push_back(Sprite(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TYPE_WOOD));
			}
			if (levelData[i][j] == 'X')
			{
				// Boxes are walls that can be moved!
				mWalls.push_back(MovableWall(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE));
				sprites.push_back(Sprite(j*BLOCK_SIZE, i*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, TYPE_WOOD));
			}
			if (levelData[i][j] == '%')
			{
				pr.SetPos(j * ACTOR_SIZE, i * ACTOR_SIZE);
			}
		}
	}
}
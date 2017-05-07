#pragma once
#include <vector>
#include "Sprite.h"
#include "common.h"

class QuadTree
{
public:
	QuadTree(int level, SDL_Rect bounds);
	~QuadTree();
	void Subdivide();
	void Clear()
	{
		objects.clear();
		for (int i = 0; i < 4; i++)
		{
			if (nodes[i] != NULL)
			{
				nodes[i]->Clear();
				nodes[i] = NULL;
			}
		}
	}
	int getIndex(SDL_Rect &pRect);
	void Insert(SDL_Rect pRect);
	std::vector<SDL_Rect> retrieve(std::vector<SDL_Rect>& returnObj, SDL_Rect pRect)
	{
		if (pLevel == MaxLevel)
			return returnObj;
		int index = getIndex(pRect);
		if (index != -1 && nodes[0] != NULL)
		{
			nodes[index]->retrieve(returnObj, pRect);
		}
		// Seems to cause excessive slowdown
		returnObj.reserve(returnObj.size() + objects.size());
		returnObj.insert(returnObj.end(), objects.begin(), objects.end());
		//returnObj = objects;
		return returnObj;
	}
	SDL_Rect bounds;
	QuadTree *nodes[4];
private:
	std::vector<SDL_Rect> objects;
	
	SDL_Rect MakeNewRect(int w, int h, int x, int y)
	{
		SDL_Rect returnRect;
		returnRect.w = w;
		returnRect.h = h;
		returnRect.x = x;
		returnRect.y = y;
		return returnRect;
	}
	int pLevel;
	const int MaxLevel = 20;
	const int MaxObjects = 60;
};


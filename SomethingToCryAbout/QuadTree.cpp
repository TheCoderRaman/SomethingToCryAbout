#include "QuadTree.h"


QuadTree::QuadTree(int level, SDL_Rect bounds)
{
	pLevel = level;
	this->bounds = bounds;
	for (int i = 0; i < 4; i++)
		nodes[i] = NULL;
}


QuadTree::~QuadTree()
{
	for (int i = 0; i < 4; i++)
		nodes[i] = NULL;
	delete[] nodes;
	Clear();
}

void QuadTree::Subdivide()
{
	if (pLevel == MaxLevel)
		return;

	int subWidth = (int)(bounds.w / 2);
	int subHeight = (int)(bounds.h / 2);
	int x = bounds.x;
	int y = bounds.y;
	
	nodes[0] = new QuadTree(pLevel+1, MakeNewRect(subWidth, subHeight, x+subWidth, y));
	nodes[1] = new QuadTree(pLevel+1, MakeNewRect(subWidth, subHeight, x, y));
	nodes[2] = new QuadTree(pLevel+1, MakeNewRect(subWidth, subHeight, x, y+subHeight));
	nodes[3] = new QuadTree(pLevel+1, MakeNewRect(subWidth, subHeight, x+subWidth, y+subHeight));
}

int QuadTree::getIndex(SDL_Rect &pRect)
{
	int index = -1;

	double vertMidPoint = bounds.x + (bounds.w / 2);

	double horiMidPoint = bounds.y + (bounds.h / 2);
	
	bool topQuadrant = (pRect.y < horiMidPoint && pRect.y + pRect.h);
	bool bottomQuadrant = (pRect.y > horiMidPoint);

	if (pRect.x < vertMidPoint && pRect.x + pRect.w < vertMidPoint)
	{
		if (topQuadrant)
			index = 1;
		else if (bottomQuadrant)
			index = 2;
	}
	else if (pRect.x > vertMidPoint)
	{
		if (topQuadrant)
			index = 0;
		else if (bottomQuadrant)
			index = 3;
	}

	return index;
}

void QuadTree::Insert(SDL_Rect pRect)
{
	if (nodes[0])
	{
		int index = getIndex(pRect);
		if (index != -1){
			nodes[index]->Insert(pRect);

			return;
		}
	}
	objects.push_back(pRect);
	if (objects.size() > MaxObjects && pLevel < MaxLevel)
	{
		if (nodes[0] == NULL) {
			Subdivide();
	//		std::printf("Subdivided\n");
		}
		int i = 0;
		while (i < objects.size())
		{
			int index = getIndex(objects[i]);
			if (index != -1){
				objects.erase(objects.begin() + i);
				nodes[index]->Insert(objects[i]);
			}
			else
				i++;
		}
	}
}
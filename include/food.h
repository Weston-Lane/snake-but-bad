#pragma once
#include "raylib.h"
#include <time.h>




class Food
{
public:
	Vector2 pos{ 0,0 };
	Color color = BLUE;

	Food(Vector2 p)
	{
		pos.x = p.x + 5;
		pos.y = p.y + 5;
	}

	void changePos(Vector2 p) 
	{
		pos.x = p.x + 5;
		pos.y = p.y + 5;
	}

	void randomizePos()
	{
		srand(time(0));
		float x = rand()%500;
		float y = rand()%440;
		changePos({ x,y });
	}
};
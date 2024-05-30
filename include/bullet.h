#pragma once
#include "raylib.h"
#include "raymath.h"
#include <time.h>
#include <cassert>
#include "macros.h"
#include "snake.h"


class Bullet
{
public:
	Vector2 vel{0,0};
	Vector2 pos{0,0};

	Vector2 pos2{0,0};
	Vector2 pos3{0,0};

	//Vector2 attackPos{};

	int speed{100};

	double rotate{0};

	Color color=PURPLE;

	void randomizeStart(Snake& s)
	{
		srand(time(0));

		int offset = 300;//sets bounds for the spawn so they do not spawn on top of player
		int maxXLeft = s.getHeadPos().x+offset;//minXLeft will just =0
		int maxYTop = s.getHeadPos().y+ offset;//minYTop will be 0
		int minXRight = s.getHeadPos().x + offset;//maxXRight =WIDTH
		int minYBottom = s.getHeadPos().y + offset;//maxYBottom=HEIGHT
		
		int LeftOrRight = rand() % 2;//random number between 0 and 1
			
		//if (LeftOrRight == 1)
		//{
		//	pos.x = (minXRight + rand()) % (WIDTH - minXRight + 1);
		//	pos.y = (minYBottom + rand()) % (HEIGHT - minYBottom + 1);				///this block shouldnt really do anything since the end is randmized anyway
		//}																			//however it did seems to prevent them spawning on top of player
		//else
		//{
		//	pos.x = (0+rand()) % (maxXLeft-0 + 1);
		//	pos.y = (0+rand()) % (maxYTop-0 + 1);
		//}


		pos.x = rand() % 500;
		pos.y = rand() % 440;
		pos2 = { pos.x - 8,pos.y + 12 };
		pos3 = { pos.x + 8,pos.y + 12 };
	}

	void update(Vector2 snakePos, double DT)
	{

		speed = 100;
		speed *= DT;

		vel = Vector2Subtract(Vector2Scale(snakePos,1.1), pos);
		vel = Vector2Normalize(vel);
		vel = Vector2Scale(vel, speed);
		//printf("%f\n", vel.x);

		pos.x += vel.x;
		pos.y += vel.y;

	}

	void renderBullet()
	{	
		pos2 = { pos.x - 8,pos.y + 12 };
		pos3 = { pos.x + 8,pos.y + 12 };

		DrawTriangle(pos,pos2, pos3, color);
	}

};

class otherBullet:public Bullet
{

public:

	otherBullet()
	{
		color = RED;
	}

	void updateOther()
	{
		
		pos.x += vel.x;
		pos.y += vel.y;

	}

	

};
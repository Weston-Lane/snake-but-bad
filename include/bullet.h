#pragma once
#include "raylib.h"
#include "raymath.h"
#include <time.h>
#include <cassert>
#include "macros.h"

class Bullet
{
public:
	Vector2 vel{0,0};
	Vector2 pos{0,0};

	Vector2 pos2{0,0};
	Vector2 pos3{0,0};

	//Vector2 attackPos{};

	int speed{200};

	int amount{};

	Color color=PURPLE;

	void randomizeStart()
	{
		srand(time(0));
		pos.x = rand() % 500;
		pos.y = rand() % 440;
		pos2 = { pos.x - 8,pos.y + 12 };
		pos3 = { pos.x + 8,pos.y + 12 };
	}

	void update(Vector2 snakePos, double DT)
	{

		speed = 150;
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
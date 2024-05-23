#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "raylib.h"



class SnakePart
{
	public:
		Vector2 pos{ 0,0 };
		Vector2 velocity{ 0,0 };
		SnakePart* next=NULL;
		SnakePart* prv=NULL;
		Color color = RED;


		SnakePart(Vector2 p)
		{
			pos = p;
			next = NULL;
			prv = NULL;
		}

		bool equalPos(Vector2 p2)
		{
			if (pos.x >p2.x - 5 &&
				pos.x < p2.x + 5 &&
				pos.y < p2.y + 5 &&
				pos.y > p2.y - 5)
				return true;
			return false;
		}
};

//snakePart *createPart(int x, int y, int s)
//{
//	snakePart *newPart=(snakePart*)malloc(sizeof(snakePart));
//	newPart->xPos = x;
//	newPart->yPos = y;
//	newPart->size = s;
//	newPart->next = NULL;
//	newPart->prv = NULL;
//	return newPart;
//}



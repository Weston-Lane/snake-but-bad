#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "raylib.h"



typedef struct snakePart
{
	int xPos;
	int yPos;
	int size;
	Vector2 velocity;
	Vector2 Pos;

	struct snakePart *next;
	struct snakePart* prv;

};

int size=0;

snakePart *createPart(int x, int y, int s)
{
	snakePart *newPart=(snakePart*)malloc(sizeof(snakePart));
	newPart->xPos = x;
	newPart->yPos = y;
	newPart->size = s;
	newPart->next = NULL;
	newPart->prv = NULL;
	return newPart;
}
void addPart(snakePart** head,int x, int y, int s)
{

	snakePart* newPart = createPart(x, y, s);

	snakePart* temp = *head;

	while (temp->next != NULL)
		temp = temp->next;
	
	temp->next = newPart;
	newPart->prv = temp;
	size++;
}


#pragma once
#include "SnakeBody.h"
#include "macros.h"
class Snake
{
 public:


	SnakePart* head= NULL;
	int size = 0;
	SnakePart* tail = NULL;
	Snake(SnakePart* h)
	{
		head = h;
	
	}


	Vector2 getHeadPos() { return head->pos; }

	void addPart(SnakePart** head)
	{
		SnakePart* temp = *head;

		while (temp->next != NULL)
			temp = temp->next;

		SnakePart* newPart = new SnakePart(temp->pos);
		temp->next = newPart;
		tail = newPart;
		newPart->prv = temp;
		size++;
	}

	void updatePos(Vector2 vel)
	{
		if (head->pos.y < -20)
			head->pos.y = HEIGHT + 10;
		if (head->pos.x < -20)
			head->pos.x = WIDTH + 10;
		if (head->pos.y > HEIGHT+20)
			head->pos.y = -10;
		if (head->pos.x > WIDTH+20)
			head->pos.x = -10;

		for (SnakePart* t = tail; t != NULL; t = t->prv)
		{
			if (t->prv != NULL)
			{
				if (vel.x < 0)
				{
					t->pos.x  = t->prv->pos.x+10;
					t->pos.y = t->prv->pos.y;
				}//going left

				if (vel.x > 0)//goin right
				{
					t->pos.x = t->prv->pos.x - 10;
					t->pos.y = t->prv->pos.y;
				}

				if (vel.y < 0)//going up
				{
					t->pos.y = t->prv->pos.y + 10;
					t->pos.x = t->prv->pos.x;
				}

				if (vel.y > 0)//going down
				{
					t->pos.y = t->prv->pos.y - 10;
					t->pos.x = t->prv->pos.x;
				}

			}

		}
	
	}

	void fullState(Snake* s)
	{
		
			DrawCircle(s->getHeadPos().x, s->getHeadPos().y, 10, GRAY);

			if (s->head->next != NULL)
				for (SnakePart* t = s->head->next; t != NULL; t = t->next)
					DrawCircle(t->pos.x, t->pos.y, 10, GRAY);
		

	
	}
	void setHeadPos(Vector2 v)
	{
		head->pos.x += v.x;
		head->pos.y += v.y;
	}



};
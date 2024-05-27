#pragma once

class PlayerController
{
public:
	int moveSpeed{ 200 };
	Vector2 velocity{ 0,0 };
	double deltaTime = 0;

	PlayerController(int m, Vector2 v)
	{
		moveSpeed = m;
		velocity = v;
	}

	void updatePlayerVelocity(bool debug)
	{
		if (!debug)
		{
			if (IsKeyPressed(KEY_A) && !(velocity.x > 0))//left
			{
				velocity.x = -(moveSpeed * deltaTime);
				velocity.y = 0;
			}
			if (IsKeyPressed(KEY_D) && !(velocity.x < 0))//right
			{
				velocity.x = (moveSpeed * deltaTime);
				velocity.y = 0;
			}
			if (IsKeyPressed(KEY_W) && !(velocity.y > 0))//up
			{
				velocity.x = 0;
				velocity.y = -(moveSpeed * deltaTime);
			}
			if (IsKeyPressed(KEY_S) && !(velocity.y < 0))//down
			{
				velocity.x = 0;
				velocity.y = (moveSpeed * deltaTime);
			}
		}
		else
		{
			if (IsKeyPressed(KEY_A))//left
			{
				velocity.x = -(moveSpeed * deltaTime);
				velocity.y = 0;
			}
			if (IsKeyPressed(KEY_D))//right
			{
				velocity.x = (moveSpeed * deltaTime);
				velocity.y = 0;
			}
			if (IsKeyPressed(KEY_W))//up
			{
				velocity.x = 0;
				velocity.y = -(moveSpeed * deltaTime);
			}
			if (IsKeyPressed(KEY_S))//down
			{
				velocity.x = 0;
				velocity.y = (moveSpeed * deltaTime);
			}
		}

	}

	void updateDT(double DT)
	{
		deltaTime = DT;
	}
	double const getDT()
	{
		return deltaTime;
	}
};
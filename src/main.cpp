
#include "raylib.h"
#include "raymath.h"
#include "SnakeBody.h"
#include "Snake.h"
#include "food.h"
#include "PlayerController.h"
#include "bullet.h"
#include "imgui.h"
#include "rlImGui.h"
#include "macros.h"
#include <cassert>
#include <vector>
#include <memory>

bool checkEaten(Snake*, Food*, double*);
void renderSnake(Snake*);
void failState();
bool checkCollision(Snake*,Bullet*);
void createBullets(Snake&, std::vector<std::shared_ptr<otherBullet>>& , int& , int&,double& );
void renderBullets(std::vector<std::shared_ptr<otherBullet>>& bullets);
//TODO: get the bullets to spawn more incrementally

int main()
{
	//SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(WIDTH, HEIGHT, "snake");
	SetTargetFPS(60);
	rlImGuiSetup(true);

	double frameTime = 0;//frame variables
	int frameCounter = 0;
	double bufferTime = 0;
	

	int moveSpeed = 300;//starting stats
	Vector2 initV{ 0,0 };
	Vector2 initPos{ WIDTH/2,HEIGHT/2 };

	PlayerController controller(moveSpeed, initV);//creates player controller with initial stats

	Snake snake(new SnakePart(initPos));//creating the head
	Food food({ WIDTH / 2,HEIGHT / 3 });//creating food
	Bullet follower;
	follower.randomizeStart();

	int countOfBull = 0;//how many bullets should be rendered
	std::vector<std::shared_ptr<otherBullet>> bullets;//vector of all the bullet data
	

	#if DEBUG//add a set number of parts from macros.h file if DEBUG is on
		for (int i = 0; i < NUMPARTS; i++)
			snake.addPart(&snake.head);
	#endif

	// Main game loop
	while (!WindowShouldClose())    
	{
		
		BeginDrawing();
		ClearBackground(DARKGRAY);
		rlImGuiBegin();

		double DT=GetFrameTime();
		
			
			if (!checkCollision(&snake,&follower)||DEBUG)//checks if there has been a collision if so, then go to failState
			{
				//player controller

				controller.updateDT(DT);//updates DT for controller
				controller.updatePlayerVelocity(DEBUG);//DEBUG is used to allow back and forth movement
				snake.setHeadPos(controller.velocity);//set head pos according to velocity
				
				//debug window
				#if (DEBUG)
					failState();
					ImGui::Begin("Debug");
					if(controller.velocity.x!=0)
						ImGui::Text("velocity: %f",controller.velocity.x/DT);
					else
						ImGui::Text("velocity: %f", controller.velocity.y/DT);
					ImGui::Text("X: %f", snake.getHeadPos().x);
					ImGui::Text("Y: %f", snake.getHeadPos().y);
					ImGui::Text("Size: %d", snake.size);
					ImGui::Text("Frame: %d", frameCounter);
					ImGui::Text("X: %f", bullet.pos.x);
					ImGui::Text("Y: %f", bullet.pos.y);
					ImGui::Text("X: %f", bullet.vel.x);
					ImGui::Text("Y: %f", bullet.vel.y);
					if (checkCollision(&snake,&bullet))
						ImGui::Text("COLLISION!");
					ImGui::End();
				#endif




				DrawRectangle(food.pos.x, food.pos.y, 10, 10, food.color);//draws the food

				if (checkEaten(&snake, &food, &bufferTime))	//checks if food eaten, randomizes a new food pos, and adds to size; 
				{											//also uses frameTime to see if long enough has passed since last food eaten to prevent mutiple collisions 
					snake.fullState(&snake);				//if food was just eaten, renders the snake grey to let someone know they cannot eat yet;
					snake.updatePos(controller.velocity);

				}
				else//if no food is eaten this frame then update and render normally
				{
					snake.updatePos(controller.velocity);
					renderSnake(&snake);
				}



				//create the bullets and render
				createBullets(snake, bullets, frameCounter, countOfBull, DT);//creates a new bullets every time size is even or just one bullet when size is odd
				renderBullets(bullets);//renders the bullets and deletes them when off screen


				follower.update(snake.getHeadPos(), DT);//updates the Bullets position and renders
				follower.renderBullet();


				frameTime += DT;
				bufferTime += DT;//frame variables just if needed


				frameCounter++;
				if (frameCounter % 200 == 0)//resets the frame counter so it doesnt get too high
					frameCounter = 0;


			}
			else
				failState();//the failState previously mentioned

		rlImGuiEnd();
		EndDrawing();
	}
	rlImGuiShutdown();

 
	CloseWindow();    


	return 0;
}

bool checkEaten(Snake* s, Food* food, double* buffer)
{
	
	if (s->getHeadPos().x > food->pos.x - 8 &&
		s->getHeadPos().x < food->pos.x + 15 &&
		s->getHeadPos().y < food->pos.y + 10 &&
		s->getHeadPos().y > food->pos.y - 10)
	{
		if (*buffer >= .5)
		{
			food->randomizePos();
			s->addPart(&s->head);
			*buffer = 0;
		}
		
		return true;
	}
	else
		return false;



}

void failState()
{
	DrawText("Game Over", WIDTH / 4+30, HEIGHT / 3, 50, RED);
}

bool checkCollision(Snake* s,Bullet* b)
{
	for (SnakePart* t = s->head->next; t != NULL; t = t->next)
		if(s->head->equalPos(t->pos))
			return true;
	if (s->head->equalBulletPos(b->pos))
		return true;


	return false;

}

void createBullets(Snake& snake, std::vector<std::shared_ptr<otherBullet>>& bullets, int& frameCounter, int& countOfBull, double& DT)
{
	if (HARD)//HARD macro is size%2==0 not sure why this makes so many spawn but its kinda fun
	{
		for (int i = 0; i < countOfBull; i++)
		{
			otherBullet* b = new otherBullet;
			std::shared_ptr<otherBullet> bs(b);//shared ptr made this work, no clue why
			bs->randomizeStart();
			bs->speed = 150;
			bs->speed *= DT;

			bs->vel = Vector2Subtract(Vector2Scale(snake.getHeadPos(), 1.1), bs->pos);
			bs->vel = Vector2Normalize(bs->vel);
			bs->vel = Vector2Scale(bs->vel, bs->speed);
			bullets.push_back(bs);
		}
		countOfBull++;
		if (countOfBull > 1)
			countOfBull = 0;
	}
}

void renderBullets(std::vector<std::shared_ptr<otherBullet>>& bullets)
{
	for (auto& i : bullets)
	{

		if (i != nullptr)
		{
			i->updateOther();
			i->renderBullet();


			if (i->pos.x > WIDTH || i->pos.y > HEIGHT || i->pos.y < 0 || i->pos.x < 0)
			{
				//bullets.erase(std::remove(bullets.begin(), bullets.end(), i), bullets.end());
				i.reset();

			}
		}

	}

}

void renderSnake(Snake* s)
{
	DrawCircle(s->getHeadPos().x, s->getHeadPos().y, 10, BLUE);

	if (s->head->next != NULL)
		for (SnakePart* t = s->head->next; t != NULL; t = t->next)
			DrawCircle(t->pos.x, t->pos.y, 10, GREEN);
}



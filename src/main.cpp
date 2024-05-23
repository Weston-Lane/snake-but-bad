
#include "raylib.h"
#include "raymath.h"
#include "SnakeBody.h"
#include "Snake.h"
#include "food.h"
#include "PlayerController.h"
#include "imgui.h"
#include "rlImGui.h"
#include "macros.h"


bool checkEaten(Snake*, Food*, double*);
void renderSnake(Snake*);
void failState();
bool checkCollision(Snake*);

/*TODO:add bullets to shoot at snake from random directions*/

int main()
{
	


	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(WIDTH, HEIGHT, "snake");
	SetTargetFPS(60);
	rlImGuiSetup(true);

	double frameTime = 0;//frame variables
	int frameCounter = 0;

	int moveSpeed = 200;//starting stats
	Vector2 initV{ 0,0 };
	Vector2 initPos{ WIDTH/2,HEIGHT/2 };

	PlayerController controller(moveSpeed, initV);//creates player controller with initial stats

	Snake snake(new SnakePart(initPos));//creating the head
	Food food({ WIDTH / 2,HEIGHT / 3 });//creating food
	
	if (DEBUG)//add a set number of parts from macros.h file if DEBUG is on
		for (int i = 0; i < NUMPARTS; i++)
			snake.addPart(&snake.head);

	// Main game loop
	while (!WindowShouldClose())    
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);
		rlImGuiBegin();

		double DT=GetFrameTime();
		

			
			if (!checkCollision(&snake)||DEBUG)//checks if there has been a collision if so, then go to failState
			{

				//player controller

				controller.updateDT(DT);//updates DT for controller
				controller.updatePlayerVelocity(DEBUG);//DEBUG is used to allow back and forth movement
				snake.setHeadPos(controller.velocity);//set head pos according to velocity


				//debug window
				if (DEBUG)
				{
					failState();
					ImGui::Begin("position");
					ImGui::Text("X: %f", snake.getHeadPos().x);
					ImGui::Text("Y: %f", snake.getHeadPos().y);
					ImGui::Text("Size: %d", snake.size);
					ImGui::Text("Frame: %d", frameCounter);
					if (checkCollision(&snake))
						ImGui::Text("COLLISION!");
					ImGui::End();
				}




				DrawRectangle(food.pos.x, food.pos.y, 10, 10, food.color);//draws the food


			
				if (checkEaten(&snake, &food, &frameTime))	//checks if food eaten, randomizes a new food pos, and adds to size; 
				{											//also uses frameTime to see if long enough has passed since last food eaten to prevent mutiple collisions 
					snake.fullState(&snake);				//if food was just eaten, renders the snake grey to let someone know they cannot eat yet;
					snake.updatePos(controller.velocity);
					
				}									
				else//if no food is eaten this frame then update and render normally
				{
					snake.updatePos(controller.velocity);
					renderSnake(&snake);
				}
									









				frameTime += DT;//frame variables just if needed
				frameCounter++;
				if (frameCounter % 100 == 0)
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

bool checkEaten(Snake* s, Food* food, double* frameTime)
{
	
	if (s->getHeadPos().x > food->pos.x - 8 &&
		s->getHeadPos().x < food->pos.x + 15 &&
		s->getHeadPos().y < food->pos.y + 10 &&
		s->getHeadPos().y > food->pos.y - 10)
	{
		if (*frameTime >= .5)
		{
			food->randomizePos();
			s->addPart(&s->head);
			*frameTime = 0;
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

bool checkCollision(Snake* s)
{
	for (SnakePart* t = s->head->next; t != NULL; t = t->next)
		if(s->head->equalPos(t->pos))
			return true;
	
	return false;

}

void renderSnake(Snake* s)
{
	DrawCircle(s->getHeadPos().x, s->getHeadPos().y, 10, GREEN);

	if (s->head->next != NULL)
		for (SnakePart* t = s->head->next; t != NULL; t = t->next)
			DrawCircle(t->pos.x, t->pos.y, 10, RED);
}




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
#include "backround.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <memory>

bool checkEaten(Snake*, Food*, double*);
void renderSnake(Snake*);
void failState();
bool checkCollision(Snake* , Bullet* , std::vector<std::shared_ptr<otherBullet>>&);
void createBullets(Snake&, std::vector<std::shared_ptr<otherBullet>>& , int& ,double& );
void renderBullets(std::vector<std::shared_ptr<otherBullet>>&);
void renderBackground(Background*);
//TODO: get the bullets to spawn more incrementally

int main()
{
	//SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(WIDTH, HEIGHT, "snake");
	SetTargetFPS(40);
	rlImGuiSetup(true);
	InitAudioDevice();

	Wave musicWav = LoadWave("assets/sounds/Linkin Park - In the End (Lyrics).wav");
	Wave eatWav = LoadWave("assets/sounds/Cartoon Munch Sound Effect edited.wav");
	Wave deathWav = LoadWave("assets/sounds/why sound effect.wav");
	Sound death = LoadSoundFromWave(deathWav);
	Sound music = LoadSoundFromWave(musicWav);
	Sound eat = LoadSoundFromWave(eatWav);

	PlaySound(music);
	bool deathCheck = true;

	double frameTime = 0;//frame variables
	int frameCounter = 0;
	double bufferTime = 0;
	

	int moveSpeed = 250;//starting stats
	Vector2 initV{ 0,0 };
	Vector2 initPos{ WIDTH/2,HEIGHT/2 };

	PlayerController controller(moveSpeed, initV);//creates player controller with initial stats
	
	Background back(LoadTexture("assets/nature_5/1.png"));//loads in all texture
	Background mid(LoadTexture("assets/nature_5/2.png"));//RELATIVE PATHS DO WORK JUST HAVE TO FIGURE OUT HOW TO ADD ASSETS TO CMAKE PATH
	Background mid2(LoadTexture("assets/nature_5/3.png"));
	Background fore(LoadTexture("assets/nature_5/4.png"));
	back.speed = 20;
	mid.speed = 40;
	mid2.speed = 60;
	fore.speed = 80;


	

	Snake snake(new SnakePart(initPos));//creating the head
	Food food({ WIDTH / 2,HEIGHT / 3 });//creating food
	Bullet follower;
	follower.randomizeStart(snake);

	
	std::vector<std::shared_ptr<otherBullet>> bullets;//vector of all the bullet data
	
	int difficulty = 50;
	bool flip = false;



	#if DEBUG//add a set number of parts from macros.h file if DEBUG is on
		for (int i = 0; i < NUMPARTS; i++)
			snake.addPart(&snake.head);
	#endif

//	// Main game loop
	while (!WindowShouldClose())    
	{
		
		BeginDrawing();
		ClearBackground(DARKGRAY);
		rlImGuiBegin();

		double DT=GetFrameTime();
		

			
			if (!checkCollision(&snake,&follower,bullets)||DEBUG)//checks if there has been a collision if so, then go to failState
			{

				back.updateBackground(DT);
				mid.updateBackground(DT);
				mid2.updateBackground(DT);
				fore.updateBackground(DT);


				renderBackground(&back);
				renderBackground(&mid);
				renderBackground(&mid2);
				renderBackground(&fore);




				DrawText(TextFormat("Score: %d", snake.size-1), 20, 20, 30, RED);//score board
				DrawText(TextFormat("Time: %lf", GetTime()), WIDTH - 250, 20, 30, RED);
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
					ImGui::Text("fX: %f", follower.pos.x);
					ImGui::Text("fY: %f", follower.pos.y);
					ImGui::Text("fvX: %f", follower.vel.x);
					ImGui::Text("fvY: %f", follower.vel.y);
					ImGui::Text("DT: %f", DT);
					if (checkCollision(&snake,&follower,bullets))
						ImGui::Text("COLLISION!");
					ImGui::End();
				#endif




				DrawRectangle(food.pos.x, food.pos.y, 10, 10, food.color);//draws the food

				if (checkEaten(&snake, &food, &bufferTime))	//checks if food eaten, randomizes a new food pos, and adds to size; 
				{											//also uses frameTime to see if long enough has passed since last food eaten to prevent mutiple collisions 
					snake.fullState(&snake);				//if food was just eaten, renders the snake grey to let someone know they cannot eat yet;
					snake.updatePos(controller.velocity);
					flip = true;
					PlaySound(eat);
				}
				else//if no food is eaten this frame then update and render normally
				{
					snake.updatePos(controller.velocity);
					renderSnake(&snake);
				}


				//create the bullets and render
				if(frameCounter>1)//BUG SOLVED: since DT is always 0 at first frame, speed of first bullet is always 0, this check prevents bullets spawing until 2 frames in
					if(frameCounter%difficulty==0)//creates a bullet every 10 frames//could be used for difficulty
						createBullets(snake, bullets, frameCounter, DT);//creates a new bullets every time size is even or just one bullet when size is odd

				renderBullets(bullets);//renders the bullets and deletes them when off screen

				
				follower.update(snake.getHeadPos(), DT);//updates the Bullets position and renders
				follower.renderBullet();


				frameTime += DT;
				bufferTime += DT;//frame variables just if needed


				frameCounter++;
				if (frameCounter % 200 == 0)//resets the frame counter so it doesnt get too high
					frameCounter = 0;

				if (snake.size % DIFFICULTY == 0&&flip&&difficulty!=1)//increments the difficulty 
				{
					difficulty = difficulty/2;
					flip = false;
				}
				

			}
			else
			{

				back.updateBackground(DT);
				mid.updateBackground(DT);
				mid2.updateBackground(DT);
				fore.updateBackground(DT);


				renderBackground(&back);
				renderBackground(&mid);
				renderBackground(&mid2);
				renderBackground(&fore);

				failState();//the failState previously mentioned
				StopSound(music);
				
				if (deathCheck)
				{
					PlaySound(death);
					deathCheck = false;
				}


				DrawText(TextFormat("Score: %d", snake.size-1), WIDTH/3, HEIGHT/2, 50, RED);//score board


			}


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

bool checkCollision(Snake* s,Bullet* b, std::vector<std::shared_ptr<otherBullet>>& bs)
{
	for (SnakePart* t = s->head->next; t != NULL; t = t->next)
		if(s->head->equalPos(t->pos))
			return true;
	if (s->head->equalBulletPos(b->pos))
		return true;

	for (auto& i : bs)
		if (s->head->equalBulletPos(i->pos))
			return true;

	return false;

}

void createBullets(Snake& snake, std::vector<std::shared_ptr<otherBullet>>& bullets, int& frameCounterl, double& DT)
{

			otherBullet* b = new otherBullet;
			std::shared_ptr<otherBullet> bs(b);//shared ptr made this work, no clue why
			bs->randomizeStart(snake);
			//bs->speed = 150;
			bs->speed *= DT;//BUG SOLVED: since DT is always 0 at first frame, speed of first bullet is always 0


			bs->vel = Vector2Subtract(Vector2Scale(snake.getHeadPos(), 1.2), bs->pos);
			bs->vel = Vector2Normalize(bs->vel);
			bs->vel = Vector2Scale(bs->vel, bs->speed);
			bullets.push_back(bs);

			
	
}

void renderBackground(Background* back)
{
	Vector2 bg1Pos{ back->xPos,0.0 };
	Vector2 bg2Pos{ back->xPos + back->texture.width * 2,0.0 };//width multiplied by 2 since scale is 2x
	DrawTextureEx(back->texture, bg1Pos, 0.0, 2.0, WHITE);
	DrawTextureEx(back->texture, bg2Pos, 0.0, 2.0, WHITE);
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

				i.reset();//removes the ptr
				bullets.erase(std::remove(bullets.begin(), bullets.end(), i), bullets.end());//removes from the vector
			

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



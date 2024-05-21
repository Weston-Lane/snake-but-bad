
#include "raylib.h"
#include "raymath.h"

#include "imgui.h"
#include "rlImGui.h"


int main()
{

	int screenWidth = 1280;
	int screenHeight = 800;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "raylib-Extras [ImGui] example - Docking");
	SetTargetFPS(144);
	rlImGuiSetup(true);


	// Main game loop
	while (!WindowShouldClose())    
	{
		BeginDrawing();
		ClearBackground(DARKGRAY);

		
		rlImGuiBegin();


		rlImGuiEnd();

		EndDrawing();

	}
	rlImGuiShutdown();

 
	CloseWindow();    


	return 0;
}
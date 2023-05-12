#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

int main(int argc, char ** argv)
{

	InitWindow(800, 800, "Essential Tower Defense");
	SetTargetFPS(60);
	SetWindowState(FLAG_VSYNC_HINT);

	while(!WindowShouldClose())
	{

		BeginDrawing();
			ClearBackground(BLACK);
			DrawText("Essential Tower Defense", 10, 100, 60, RED);
		EndDrawing();

	}

	return EXIT_SUCCESS;
}
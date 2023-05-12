#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "tile.h"
#include "level.h"
#include "inventory.h"
#include "item.h"

int main(int argc, char ** argv)
{

	InitWindow(800, 800, "Essential Tower Defense");
	SetTargetFPS(60);
	SetWindowState(FLAG_VSYNC_HINT);

	//Loading texture pack
	TexturePack pack = {0};
	SetItemTexture(&pack, Turret, "images/turret.png");
	SetItemTexture(&pack, Healer, "images/healer.png");
	SetItemTexture(&pack, Bomb, "images/bomb.png");

	//Loading tiles
	Level l = LoadLevel("levels/test.lvl");
	
	//Inventory
	Inventory inv = {0};
	inv.x = 10.f;
	inv.y = 10.f;
	inv.item_size = 70.f;
	inv.texture_pack = &pack;

	AddItem(&inv, Turret);
	AddItem(&inv, Bomb);
	AddItem(&inv, Healer);

	//Building list (fills when user clicks)
	Building buildings[100] = {0};
	int buildings_count = 0;

	//Camera
	Camera2D cam = {0};
	cam.zoom = 1.f;

	const float zoom_precision = 15.f;

	while(!WindowShouldClose())
	{

		//Camera zoom control
		float scrolling = GetMouseWheelMove()/zoom_precision;
		
		if(scrolling != 0.f && cam.zoom + scrolling > 0.1f && cam.zoom + scrolling < 2.f)
		{
			cam.zoom += scrolling;
		}

		//Camera position control
		if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			cam.target.x -= GetMouseDelta().x / cam.zoom;
			cam.target.y -= GetMouseDelta().y / cam.zoom;
		}
		//Left click
		else if(InventoryClicked(&inv))
		{}
		else if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			//Placing new building if tile is valid (Not a path and not already taken)
			Rectangle rect = {GetScreenToWorld2D(GetMousePosition(), cam).x,
							  GetScreenToWorld2D(GetMousePosition(), cam).y,
							  100.f, 100.f};
			int can_place = 1;
			for(int i = 0; i < buildings_count; i++)
			{
				Rectangle curr = {buildings[i].x, buildings[i].y, buildings[i].size, buildings[i].size};
				if(CheckCollisionRecs(rect, curr))
				{
					can_place = 0;
					break;
				}
			}
			if(l.tiles[(int) rect.y/100][(int) rect.x/100].type == Path)
			{
				can_place = 0;
			}
			if(can_place)
			{
				buildings[buildings_count].x = rect.x;
				buildings[buildings_count].y = rect.y;
				buildings[buildings_count].size = 100.f;
				buildings[buildings_count].rotation = 0.f;
				buildings[buildings_count].texture = &(pack.textures[inv.items[inv.selected]]);
				buildings_count ++;
			}
		}

		BeginDrawing();
			ClearBackground(BLACK);
			
			BeginMode2D(cam);
				//Drawing tiles
				for(int y = 0; y < l.height; y++)
				{
					for(int x = 0; x < l.width; x++)
						DrawRectangleV(l.tiles[y][x].position, l.tiles[y][x].size, l.tiles[y][x].color);
				}
				//Drawing buildings
				for(int i = 0; i < buildings_count; i++)
				{
					buildings[i].rotation += 1.f;
					DrawBuilding(buildings[i]);
				}
			EndMode2D();
		
			DrawInventory(inv);
		EndDrawing();

	}

	//End
	UnloadTexturePack(&pack);

	return EXIT_SUCCESS;
}
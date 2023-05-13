#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <string.h>
#include "tile.h"
#include "level.h"
#include "inventory.h"
#include "item.h"
#include "mob.h"

#define MAX_MOB_COUNT 100

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
	SetItemTexture(&pack, Rip, "images/rip.png");

	//Loading tiles
	Level l = LoadLevel("levels/test.lvl");
	
	//Inventory
	Inventory inv = {0};
	inv.x = 10.f;
	inv.y = 10.f;
	inv.item_size = 70.f;
	inv.texture_pack = &pack;

	AddItem(&inv, Turret, 150);
	AddItem(&inv, Bomb, 200);
	AddItem(&inv, Healer, 25);

	int money = 150;

	//Building list (fills when user clicks)
	Building buildings[100] = {0};
	int buildings_count = 0;

	//Mob list
	Mob mobs[MAX_MOB_COUNT] = {0};
	int mobs_count = 0;

	//Camera
	Camera2D cam = {0};
	cam.zoom = 1.f;

	const float zoom_precision = 15.f;

	int frame_count = 0;
	while(!WindowShouldClose())
	{

		if(frame_count % 10 == 0)
			money ++;

		if(mobs_count < MAX_MOB_COUNT && frame_count%60 == 0)
		{
			mobs[mobs_count] = CreateMob(l);
			mobs_count ++;
		}

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
		else if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && money >= inv.costs[inv.selected])
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
				money -= inv.costs[inv.selected];

				buildings[buildings_count] = CreateBuilding(rect.x, rect.y, inv.items[inv.selected], &pack);
				buildings_count ++;
			}
		}

		for(int i = 0; i < mobs_count; i++)
			UpdateMob(&mobs[i], l);
		for(int i = 0; i < buildings_count; i++)
		{
			UpdateBuilding(&buildings[i], mobs, mobs_count, buildings, buildings_count, &pack);
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
					DrawBuilding(buildings[i]);

				//Drawing mobs
				for(int i = 0; i < mobs_count; i++)
					DrawMob(mobs[i]);

			EndMode2D();
		
			DrawInventory(inv, money);
			char money_s[10];
			sprintf(money_s, "%d", money);
			char to_draw[18] = "Money : ";
			strcat(to_draw, money_s);
			strcat(to_draw, " $");

			DrawText(to_draw, 10, 650, 20, YELLOW);

			DrawFPS(10, 700);
		EndDrawing();

		frame_count++;
	}

	//End
	UnloadTexturePack(&pack);

	return EXIT_SUCCESS;
}
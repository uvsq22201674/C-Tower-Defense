#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <raylib.h>
#include "mob.h"

enum Item
{
	Turret = 1,
	Healer = 2,
	Bomb = 3,
	Rip = 4
};
typedef enum Item Item;

struct Building
{
	float x; // x position in world
	float y; // y position in world
	float size; // size of every of its side

	float rotation;

	Texture2D * texture;
	Item type;

	Vector2 target;

	int life;
};
typedef struct Building Building;

struct TexturePack
{
	Texture2D textures[24];
};
typedef struct TexturePack TexturePack;

void SetItemTexture(TexturePack *, Item, char *);
void UnloadTexturePack(TexturePack * pack); // Frees loaded textures
void UpdateBuilding(Building * b, Mob * mobs, int mobs_count, Building * buildings, int buildings_count, TexturePack * pack);
void DrawBuilding(Building);

#endif
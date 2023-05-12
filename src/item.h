#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <raylib.h>

enum Item
{
	Turret = 1,
	Healer = 2,
	Bomb = 3
};
typedef enum Item Item;

struct Building
{
	float x;
	float y;
	float size;

	float rotation;

	Texture2D * texture;
};
typedef struct Building Building;

struct TexturePack
{
	Texture2D textures[24];
};
typedef struct TexturePack TexturePack;

void SetItemTexture(TexturePack *, Item, char *);
void UnloadTexturePack(TexturePack * pack);
void DrawBuilding(Building);

#endif
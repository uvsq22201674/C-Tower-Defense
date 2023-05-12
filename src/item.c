#include "item.h"

void SetItemTexture(TexturePack * pack, Item item, char * path)
{
	pack->textures[item] = LoadTexture(path);
}
void UnloadTexturePack(TexturePack * pack)
{
	for(int i = 0; i < 24; i++)
	{
		UnloadTexture(pack->textures[i]);
	}
}
void DrawBuilding(Building b)
{
	Vector2 origin = {b.size / 2.f, b.size / 2.f};
	Rectangle source = {0, 0, b.texture->width, b.texture->height};
	Rectangle dest = {b.x, b.y, b.size, b.size};

	DrawTexturePro(*b.texture, source, dest, origin, b.rotation, WHITE);
}
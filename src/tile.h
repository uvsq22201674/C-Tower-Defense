#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <raylib.h>

enum TileType
{
	Path = 1 << 0,
	Grass = 1 << 1,
	Wall = 1 << 2
};
typedef enum TileType TileType;

struct Tile
{
	Vector2 position;
	Vector2 size;

	Color color;
	TileType type;
};
typedef struct Tile Tile;

Tile CreateTile(float x, float y, float width, float height, TileType type);
int IsInTile(Tile tile, float x, float y);
Color TileTypeColor(TileType);

#endif
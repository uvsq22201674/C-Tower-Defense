#include "tile.h"
#include "stdio.h"

Tile CreateTile(float x, float y, float width, float height, TileType type)
{
	Tile tile = {
		{x, y},
		{width, height},
		TileTypeColor(type),
		type
	};

	return tile;
}

int IsInTile(Tile tile, float x, float y)
{
	return (x >= tile.position.x && x <= tile.position.x + tile.size.x
		 && y >= tile.position.y && y <= tile.position.y + tile.size.y);
}

Color TileTypeColor(TileType type)
{
	Color color = {0};
	color.a = 255;

	switch(type)
	{
	case Path:
		color.r = 200;
		color.g = 200;
		color.b = 150;
	break;
	case Grass:
		color.r = 50;
		color.g = 200;
		color.b = 30;
	break;
	case Wall:
		color.r = 100;
		color.g = 100;
		color.b = 100;
	break; 
	}

	return color;
}

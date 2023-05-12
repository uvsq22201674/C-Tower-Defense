#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "tile.h"

struct Level
{
	Tile tiles[200][200];

	int width; // Nbr of tiles in width
	int height; // Nbr of tiles in height
	//TODO
};
typedef struct Level Level;

Level LoadLevel(const char * path);

#endif
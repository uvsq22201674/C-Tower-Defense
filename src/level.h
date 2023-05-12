#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include "tile.h"

struct Level
{
	Tile tiles[200][200];

	int width;
	int height;
	//TODO
};
typedef struct Level Level;

Level LoadLevel(const char * path);

#endif
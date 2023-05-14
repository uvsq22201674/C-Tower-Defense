#ifndef MOB_H_INCLUDED
#define MOB_H_INCLUDED

#include <raylib.h>
#include "level.h"

enum Direction
{
	Up = 0,
	Left = 1,
	Down = 2,
	Right = 3
};
typedef enum Direction Direction;

enum Specie
{
	Zox = 1 << 0,
	Barxeid = 1 << 1,
	Sundar = 1 << 2
};
typedef enum Specie Specie;

struct Mob
{
	Rectangle body;

	int max_life;
	int life;

	Direction dir;

	int dead;

	Specie specie;
};
typedef struct Mob Mob;

Mob CreateMob(Level, Specie);
void UpdateMob(Mob *, Level, int*);
void DrawMob(Mob);
Vector2 DirectionToVector(Direction);
int IsTilePath(Level, float, float);

#endif
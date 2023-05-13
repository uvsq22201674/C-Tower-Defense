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

struct Mob
{
	Rectangle body;

	int life;

	Direction dir;

	int dead;
};
typedef struct Mob Mob;

Mob CreateMob(Level);
void UpdateMob(Mob *, Level);
void DrawMob(Mob);
Vector2 DirectionToVector(Direction);
int IsTilePath(Level, float, float);

#endif
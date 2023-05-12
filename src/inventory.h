#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

#include <raylib.h>
#include "item.h"

struct Inventory
{
	float x;
	float y;
	float item_size;

	int selected;

	int items[8];
	int costs[8];

	TexturePack * texture_pack;
};
typedef struct Inventory Inventory;

void AddItem(Inventory *, int);
void DrawInventory(Inventory);
int InventoryClicked(Inventory *);

#endif
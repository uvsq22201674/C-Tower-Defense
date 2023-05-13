#ifndef INVENTORY_H_INCLUDED
#define INVENTORY_H_INCLUDED

#include <raylib.h>
#include "item.h"

struct Inventory
{
	float x; // x position in world
	float y; // y position in world
	float item_size; // item size in slot

	int selected; // index of selected slot

	int items[8]; // array of items
	int costs[8]; // gold cost of item (Not currently used)

	TexturePack * texture_pack; // Texture pack used to render items in slots
};
typedef struct Inventory Inventory;

void AddItem(Inventory *, int, int);
void DrawInventory(Inventory, int);
int InventoryClicked(Inventory *); // Process click event and returns 1 if inventory is clicked, 0 if not.

#endif
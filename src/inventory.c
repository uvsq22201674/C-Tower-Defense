#include "inventory.h"
#include "item.h"
#include <stdio.h>

void AddItem(Inventory * inv, int item)
{
	for(int i = 0; i < 8; i++)
	{
		if(inv->items[i] == 0)
		{
			inv->items[i] = item;
			break;
		}
	}
}

void DrawInventory(Inventory inv)
{
	DrawRectangle(inv.x, inv.y, inv.item_size + 10, (inv.item_size + 5) * 8 + 5, BROWN);

	for(int i = 0; i < 8; i ++)
	{
		Color color = MAROON;
		if(inv.selected == i)
			color = YELLOW;

		DrawRectangle(inv.x + 5, inv.y + i * inv.item_size + 5 * (i + 1), inv.item_size, inv.item_size, color);

		if(inv.items[i] != 0 && inv.texture_pack != 0)
		{
			Texture2D * t = &(inv.texture_pack->textures[inv.items[i]]);
			Vector2 pos = {inv.x + 5, inv.y + i * inv.item_size + 5 * (i + 1)};
			DrawTextureEx(*t, pos, 0.f, inv.item_size / (float) (t->width), WHITE);
		}
	}
}

int InventoryClicked(Inventory * inv)
{
	Vector2 mouse = GetMousePosition();
	if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && mouse.x >= inv->x && mouse.y >= inv->y
											&& mouse.x <= inv->x + inv->item_size
											&& mouse.y <= inv->y + inv->item_size * 8)
	{

		inv->selected = (int) ((mouse.y - inv->y - 5.f)/(inv->item_size + 5.f));

		return 1;
	}else return 0;
}
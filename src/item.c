#include "item.h"
#include <math.h>

Building CreateBuilding(float x, float y, Item type, TexturePack * pack)
{
	Building b;
	b.x = x;
	b.y = y;
	b.size = 100.f;
	b.type = type;
	b.rotation = 0.f;
	b.texture = &pack->textures[type];
	b.target.x = 0;
	b.target.y = 0;

	switch(type)
	{
		case Turret:
			b.life = 100;
			b.damages = 1;
		break;
		case Healer:
			b.life = 10;
			b.damages = 1;
		break; 
		case  Bomb:
			b.life = 10;
			b.damages = 50;
		break;
	}

	return b;
}

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

void UpdateBuilding(Building * b, Mob * mobs, int mobs_count, Building * buildings, int buildings_count, TexturePack * pack)
{
	if(b->life <= 0)
		{
			b->target.x = 0;
			b->target.y = 0;
			b->rotation = 0.f;
			b->texture = &pack->textures[Rip];
			return;
		}

	if(GetRandomValue(1, 10) == 1)
		b->life --;

	if(b->type == Turret)
	{
		int targeted = 0;
		for(int i = 0; i < mobs_count; i++)
		{
			Mob m = mobs[i];

			float norm = sqrt(pow(b->x - m.body.x - m.body.width / 2.f, 2) + pow(b->y - m.body.y - m.body.height / 2.f, 2));

			if(m.dead == 0 && norm < 200)
			{
				float angle = acos((m.body.x + m.body.width / 2.f - b->x)/norm);
				if(m.body.y + m.body.height/2.f < b->y)
					angle = -angle;

				b->rotation = angle * (180.f / 3.1416f);
				b->target.x = m.body.x + m.body.width / 2.f;
				b->target.y = m.body.y + m.body.height / 2.f;

				mobs[i].life -= b->damages;

				targeted = 1;
				break;
			}
		}
		if(!targeted)
		{
			b->target.x = 0;
			b->target.y = 0;
			b->rotation ++;
		}
	}
	else if(b->type == Healer)
	{
		int targeted = 0;
		for(int i = 0; i < buildings_count; i++)
		{
			Building m = buildings[i];
			if(b == &buildings[i])continue;

			float norm = sqrt(pow(b->x - m.x, 2) + pow(b->y - m.y, 2));

			if(m.life < 100 && m.life > 0 && m.type != Healer && norm < 200)
			{
				float angle = acos((m.x - b->x)/norm);
				if(m.y < b->y)
					angle = -angle;

				b->rotation = angle * (180.f / 3.1416f);

				b->target.x = m.x;
				b->target.y = m.y;

				buildings[i].life += b->damages;

				targeted = 1;
				break;
			}
		}
		if(!targeted)
		{
			b->target.x = 0;
			b->target.y = 0;
			b->rotation ++;
		}
	}
	else if(b->type == Bomb)
	{
		for(int i = 0; i < mobs_count; i++)
		{
			Mob m = mobs[i];

			float norm = sqrt(pow(b->x - m.body.x - m.body.width / 2.f, 2) + pow(b->y - m.body.y - m.body.height / 2.f, 2));

			if(m.dead == 0 && norm < 500)
			{
				mobs[i].life -= b->damages;
				b->life = 0;
			}
		}
	}
	
}
void DrawBuilding(Building b)
{
	Vector2 origin = {b.size / 2.f, b.size / 2.f};
	Rectangle source = {0, 0, b.texture->width, b.texture->height};
	Rectangle dest = {b.x, b.y, b.size, b.size};

	if(b.target.x != 0 && b.target.y != 0)
	{
		Vector2 b_pos = {b.x, b.y};
		DrawLineEx(b_pos, b.target, 10.f, RED);
	}
	DrawTexturePro(*b.texture, source, dest, origin, b.rotation, WHITE);
	
	if(b.life >0)
		DrawRectangle(b.x - 50.f, b.y - 48.f, 100.f, 10.f, RED);
		DrawRectangle(b.x - 50.f, b.y - 48.f, b.life, 10.f, GREEN);
}
#include "mob.h"

Mob CreateMob(Level l)
{
	Mob to_return = {0};
	to_return.body.width = 64.f;
	to_return.body.height = 64.f;
	to_return.life = 100;
	to_return.dir = Up;

	for(int y = 0; y < l.height; y++)
	{
		for(int x = 0; x < l.width; x++)
		{
			if(l.tiles[y][x].type == Path)
			{
				to_return.body.x = x * l.tiles[y][x].size.x + 16.f;
				to_return.body.y = y * l.tiles[y][x].size.y + 16.f;
			}
		}
	}

	return to_return;
}

void UpdateMob(Mob * m, Level l)
{
	if(m->dead)return;

	Vector2 futur_pos = {m->body.x + m->body.width / 2.f, m->body.y + m->body.height / 2.f};
	Vector2 dir_v = DirectionToVector(m->dir);
	futur_pos.x += dir_v.x * 48.f;
	futur_pos.y += dir_v.y * 48.f;

	if(m->life <= 0 || futur_pos.x > l.width * 100.f || futur_pos.y < 0.f)
	{
		m->dead = 1;
		return;
	}

	if(!IsTilePath(l, futur_pos.x, futur_pos.y))
	{
		//Path blocked
		switch(m->dir)
		{
			case Up:
				if(IsTilePath(l, m->body.x - 64.f, m->body.y))
					m->dir = Left;
				else if(IsTilePath(l, m->body.x + 64.f, m->body.y))
					m->dir = Right;
			break;
			case Left:
				if(IsTilePath(l, m->body.x, m->body.y - 64.f))
					m->dir = Up;
				else if(IsTilePath(l, m->body.x, m->body.y + 64.f))
					m->dir = Down;
			break;
			case Right:
				if(IsTilePath(l, m->body.x, m->body.y - 64.f))
					m->dir = Up;
			break;
			case Down:
				if(IsTilePath(l, m->body.x - 64.f, m->body.y))
					m->dir = Left;
				else if(IsTilePath(l, m->body.x + 64.f, m->body.y))
					m->dir = Right;
			break; 
		}
	}
	else
	{
		m->body.x += dir_v.x * 5.f;
		m->body.y += dir_v.y * 5.f;
	}
}

void DrawMob(Mob m)
{
	if(m.dead == 1) return;

	DrawRectangleRec(m.body, RED);
	DrawRectangle(m.body.x - 16.f, m.body.y - 16.f, m.body.width + 32.f, 10.f, RED);
	DrawRectangle(m.body.x - 16.f, m.body.y - 16.f, (float) (m.life)/100.f * (m.body.width + 32.f), 10.f, GREEN);
}

Vector2 DirectionToVector(Direction d)
{

	Vector2 to_return = {0};
	switch(d)
	{
		case Up:
			to_return.y = -1.f;
		break;
		case Left:
			to_return.x = -1.f;
		break;
		case Down:
			to_return.y = 1.f;
		break;
		case Right:
			to_return.x = 1.f;
		break;  
	}

	return to_return;

}
int IsTilePath(Level l, float x, float y)
{
	return (l.tiles[(int) (y/100.f)][(int) (x/100.f)].type == Path);
}
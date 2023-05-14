#include "mob.h"

Mob CreateMob(Level l, Specie s)
{
	Mob to_return = {0};
	to_return.body.width = 64.f;
	to_return.body.height = 64.f;
	to_return.max_life = 100;
	to_return.dir = Up;
	to_return.specie = s;

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
	if(s & Barxeid)
	{
		to_return.max_life = 300;
		
		to_return.body.width = 100.f;
		to_return.body.height = 100.f;
		to_return.body.x -= 16.f;
		to_return.body.y -= 16.f;
	}
	to_return.life = to_return.max_life;

	return to_return;
}

void UpdateMob(Mob * m, Level l, int * passed)
{
	if(m->dead)return;

	Vector2 futur_pos = {m->body.x + m->body.width / 2.f, m->body.y + m->body.height / 2.f};
	Vector2 dir_v = DirectionToVector(m->dir);
	futur_pos.x += dir_v.x * (m->body.width/2.f + 16.f);
	futur_pos.y += dir_v.y * (m->body.height/2.f + 16.f);;

	if(m->life <= 0 || futur_pos.x > l.width * 100.f || futur_pos.y < 0.f)
	{
		if(m->life > 0)*(passed) = *(passed) + 1;

		m->dead = 1;
		return;
	}

	if(!IsTilePath(l, futur_pos.x, futur_pos.y))
	{
		//Path blocked
		switch(m->dir)
		{
			case Up:
				if(IsTilePath(l, m->body.x + m->body.width/2.f - 100.f, m->body.y + m->body.height/2.f))
					m->dir = Left;
				else if(IsTilePath(l, m->body.x + m->body.width/2.f + 100.f, m->body.y + m->body.height/2.f))
					m->dir = Right;
			break;
			case Left:
				if(IsTilePath(l, m->body.x + m->body.width/2.f, m->body.y + m->body.height/2.f - 100.f))
					m->dir = Up;
				else if(IsTilePath(l, m->body.x + m->body.width/2.f, m->body.y + m->body.height/2.f + 100.f))
					m->dir = Down;
			break;
			case Right:
				if(IsTilePath(l, m->body.x + m->body.width/2.f, m->body.y + m->body.height/2.f - 100.f))
					m->dir = Up;
				else if(IsTilePath(l, m->body.x + m->body.width/2.f, m->body.y + m->body.height/2.f + 100.f))
					m->dir = Down;
			break;
			case Down:
				if(IsTilePath(l, m->body.x + m->body.width/2.f - 100.f, m->body.y + m->body.height/2.f))
					m->dir = Left;
				else if(IsTilePath(l, m->body.x + m->body.width/2.f + 100.f, m->body.y + m->body.height/2.f))
					m->dir = Right;
			break; 
		}
	}
	else
	{
		float speed = 5.f;

		if(m->specie & Sundar)
			speed = 10.f;

		m->body.x += dir_v.x * speed;
		m->body.y += dir_v.y * speed;
	}
}

void DrawMob(Mob m)
{
	if(m.dead == 1) return;

	Color col = RED;
	if(m.specie & Sundar)
		col = ORANGE;
	DrawRectangleRec(m.body, col);
	
	DrawRectangle(m.body.x - 16.f, m.body.y - 16.f, m.body.width + 32.f, 10.f, RED);
	DrawRectangle(m.body.x - 16.f, m.body.y - 16.f, (float) (m.life)/(float) (m.max_life) * (m.body.width + 32.f), 10.f, GREEN);
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
#include "level.h"
#include <stdio.h>

Level LoadLevel(const char * path)
{

	FILE * file;
	file = fopen(path, "r");

	Level loaded = {0};

	if(file == NULL)
	{
		printf("Error : Could not open file %s\n", path);
		return loaded;
	}

	char swidth[255];
	char sheight[255];

	int x = 0;
	int y = 0;

	int index = 0;
	int state = 0;
	char road = '0';

	do
	{
		road = fgetc(file);

		if(road != EOF)
		{
			switch(state)
			{
			case 0:
				if(road != ',')
				{
					swidth[index] = road;
					index ++;
				}
				else
				{
					swidth[index] = '\0';
					index = 0;
					state ++;
				}
			break;
			case 1:
				if(road != '\n')
				{
					sheight[index] = road;
					index ++;
				}
				else
				{
					sheight[index] = '\0';
					loaded.width = strtol(swidth, '\0', 10);
					loaded.height = strtol(sheight, '\0', 10);

					index = 0;
					state ++;
				}
			break;
			case 2:
				if(road != '\n')
				{
					TileType type = Path;
					if(road == '1')
						type = Grass;
					else if(road == '2')
						type = Wall;

					loaded.tiles[y][x] = CreateTile((float) x * 100,
													(float) y * 100,
													100.f,
													100.f,
													type
					);
					x++;
				}
				else
				{
					x = 0;
					y++;
				}
			break; 

			}
		}

	}while(road != EOF);

	fclose(file);

	return loaded;
}
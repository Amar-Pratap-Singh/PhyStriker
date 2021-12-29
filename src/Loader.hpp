#pragma once
#include "Tile.hpp"
#include "Entity.hpp"
#include <vector>
#include "Ball.hpp"

using namespace std;

class Loader
{
private:
	vector<SDL_Texture *> entities;

public:
	// 0 : tile32 light
	// 1 : tile32 dark
	// 2 : tile64 light
	// 3 : tile64 dark
	// 4 : ball
	// 5 : hole
	// 6 : shadow
	Loader(vector<SDL_Texture *> e)
	{
		entities = e;
	}
	vector<Entity> load_tiles(int level)
	{
		vector<Entity> tiles = {};
		switch (level)
		{
			case (1):
			{
				tiles.push_back(Tile(24 + 32 * 8, 24 + 32 * 2, entities[1]));
				tiles.push_back(Tile(24 + 32 * 6, 24 + 32 * 2, entities[1]));
				tiles.push_back(Tile(24 + 32 * 10, 24 + 32 * 2, entities[1]));

				tiles.push_back(Tile(24 + 32 * 8, 24 + 32 * 11, entities[0]));
				tiles.push_back(Tile(24 + 32 * 6, 24 + 32 * 11, entities[0]));
				tiles.push_back(Tile(24 + 32 * 10, 24 + 32 * 11, entities[0]));

				tiles.push_back(Entity(24 + 32 * 8, 24 + 32 * 4, entities[5]));
				tiles.push_back(Entity(24 + 32 * 8, 24 + 32 * 9, entities[4]));
				break;
			}
			
			case (2):
			{
				tiles.push_back(Tile(24 + 32 * 8, 24 + 32 * 5, entities[1]));
				tiles.push_back(Tile(24 + 32 * 9, 24 + 32 * 5, entities[1]));
				tiles.push_back(Tile(24 + 32 * 8, 24 + 32 * 6, entities[1]));
				tiles.push_back(Tile(24 + 32 * 9, 24 + 32 * 6, entities[1]));

				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 2, entities[0]));
				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 2, entities[0]));

				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 9, entities[0]));
				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 9, entities[0]));

				tiles.push_back(Entity(24 + 32 * 8 + 10, 24 + 32 * 2, entities[5]));
				tiles.push_back(Entity(24 + 32 * 8 + 10, 24 + 32 * 9, entities[4]));
				break;
			}

			case (3):
			{
				/*tiles.push_back(Tile(24 + 32 * 2, 24 + 32 * 0, entities[1]));
				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 2, entities[0]));
				tiles.push_back(Tile(24 + 32 * 6, 24 + 32 * 4, entities[1]));*/
				tiles.push_back(Tile(24 + 32 * 8, 24 + 32 * 6, entities[0]));
				tiles.push_back(Tile(24 + 32 * 6, 24 + 32 * 8, entities[1]));
				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 10, entities[0]));
				tiles.push_back(Tile(24 + 32 * 2, 24 + 32 * 12, entities[1]));

				/*tiles.push_back(Tile(24 + 32 * 15, 24 + 32 * 12, entities[1]));
				tiles.push_back(Tile(24 + 32 * 13, 24 + 32 * 10, entities[0]));
				tiles.push_back(Tile(24 + 32 * 11, 24 + 32 * 8, entities[1]));
				tiles.push_back(Tile(24 + 32 * 9, 24 + 32 * 6, entities[0]));*/
				tiles.push_back(Tile(24 + 32 * 10, 24 + 32 * 4, entities[1]));
				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 2, entities[0]));
				tiles.push_back(Tile(24 + 32 * 14, 24 + 32 * 0, entities[1]));

				tiles.push_back(Entity(24 + 32 * 8.5, 20 + 32 * 0, entities[5]));
				tiles.push_back(Entity(24 + 32 * 8.5, 30 + 32 * 12, entities[4]));
				break;
			}
			case (4):
			{

				tiles.push_back(Tile(24 + 32 * 3, 24 + 32 * 2, entities[0]));
				tiles.push_back(Tile(24 + 32 * 3, 24 + 32 * 4, entities[0]));
				tiles.push_back(Tile(24 + 32 * 3, 24 + 32 * 6, entities[0]));
				tiles.push_back(Tile(24 + 32 * 3, 24 + 32 * 8, entities[0]));
				tiles.push_back(Tile(24 + 32 * 3, 24 + 32 * 10, entities[0]));

				tiles.push_back(Tile(24 + 32 * 9, 24 + 32 * 2, entities[1]));
				tiles.push_back(Tile(24 + 32 * 9, 24 + 32 * 4, entities[1]));
				tiles.push_back(Tile(24 + 32 * 9, 24 + 32 * 6, entities[1]));
				tiles.push_back(Tile(24 + 32 * 9, 24 + 32 * 8, entities[1]));
				tiles.push_back(Tile(24 + 32 * 9, 24 + 32 * 10, entities[1]));

				tiles.push_back(Tile(24 + 32 * 15, 24 + 32 * 2, entities[0]));
				tiles.push_back(Tile(24 + 32 * 15, 24 + 32 * 4, entities[0]));
				tiles.push_back(Tile(24 + 32 * 15, 24 + 32 * 6, entities[0]));
				tiles.push_back(Tile(24 + 32 * 15, 24 + 32 * 8, entities[0]));
				tiles.push_back(Tile(24 + 32 * 15, 24 + 32 * 10, entities[0]));

				tiles.push_back(Tile(24 + 32 * 3, 24 + 32 * 0, entities[5]));
				tiles.push_back(Tile(24 + 32 * 15, 24 + 32 * 12, entities[4]));
				break;
			}
			case (5):
			{
				tiles.push_back(Tile(24 + 32 * 3, 24 + 32 * 12, entities[0]));
				tiles.push_back(Tile(24 + 32 * 5, 24 + 32 * 10, entities[1]));
				tiles.push_back(Tile(24 + 32 * 7, 24 + 32 * 8, entities[0]));
				tiles.push_back(Tile(24 + 32 * 9, 24 + 32 * 6, entities[1]));

				tiles.push_back(Tile(24 + 32 * 15, 24 + 32 * 12, entities[0]));
				tiles.push_back(Tile(24 + 32 * 13, 24 + 32 * 10, entities[1]));
				tiles.push_back(Tile(24 + 32 * 11, 24 + 32 * 8, entities[0]));
				tiles.push_back(Tile(24 + 32 * 5, 24 + 32 * 12, entities[0]));
				tiles.push_back(Tile(24 + 32 * 7, 24 + 32 * 12, entities[0]));

				tiles.push_back(Tile(24 + 32 * 11, 24 + 32 * 12, entities[0]));
				tiles.push_back(Tile(24 + 32 * 13, 24 + 32 * 12, entities[0]));

				tiles.push_back(Tile(24 + 32 * 7, 24 + 32 * 4, entities[0]));
				tiles.push_back(Tile(24 + 32 * 5, 24 + 32 * 2, entities[1]));
				tiles.push_back(Tile(24 + 32 * 3, 24 + 32 * 0, entities[0]));

				tiles.push_back(Tile(24 + 32 * 15, 24 + 32 * 0, entities[0]));
				tiles.push_back(Tile(24 + 32 * 13, 24 + 32 * 2, entities[1]));
				tiles.push_back(Tile(24 + 32 * 11, 24 + 32 * 4, entities[0]));

				tiles.push_back(Tile(24 + 32 * 5, 24 + 32 * 0, entities[0]));
				tiles.push_back(Tile(24 + 32 * 7, 24 + 32 * 0, entities[0]));

				tiles.push_back(Tile(24 + 32 * 11, 24 + 32 * 0, entities[0]));
				tiles.push_back(Tile(24 + 32 * 13, 24 + 32 * 0, entities[0]));

				tiles.push_back(Entity(24 + 32 * 9, 24 + 32 * 0, entities[5]));
				tiles.push_back(Entity(24 + 32 * 9, 24 + 32 * 12, entities[4]));
				break;
			}
			case (6):
			{
				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 8, entities[0]));
				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 6, entities[1]));
				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 4, entities[0]));
				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 10, entities[1]));
				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 12, entities[0]));

				tiles.push_back(Tile(24 + 32 * 6, 24 + 32 * 4, entities[1]));
				tiles.push_back(Tile(24 + 32 * 8, 24 + 32 * 4, entities[0]));
				tiles.push_back(Tile(24 + 32 * 10, 24 + 32 * 4, entities[1]));
				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 4, entities[0]));

				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 6, entities[1]));
				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 8, entities[0]));
				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 10, entities[1]));
				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 12, entities[0]));

				tiles.push_back(Tile(24 + 32 * 6, 24 + 32 * 12, entities[1]));
				tiles.push_back(Tile(24 + 32 * 8, 24 + 32 * 12, entities[0]));
				tiles.push_back(Tile(24 + 32 * 10, 24 + 32 * 12, entities[1]));

				tiles.push_back(Tile(24 + 32 * 6, 24 + 32 * 2, entities[0]));
				tiles.push_back(Tile(24 + 32 * 8, 24 + 32 * 0, entities[1]));
				tiles.push_back(Tile(24 + 32 * 10, 24 + 32 * 2, entities[0]));

				tiles.push_back(Tile(24 + 32 * 6, 24 + 32 * 10, entities[0]));
				tiles.push_back(Tile(24 + 32 * 6, 24 + 32 * 8, entities[1]));
				tiles.push_back(Tile(24 + 32 * 8, 24 + 32 * 8, entities[0]));
				tiles.push_back(Tile(24 + 32 * 10, 24 + 32 * 8, entities[1]));
				tiles.push_back(Tile(24 + 32 * 10, 24 + 32 * 10, entities[0]));

				tiles.push_back(Entity(24 + 32 * 8, 24 + 32 * 10, entities[5]));
				tiles.push_back(Entity(24 + 32 * 8, 24 + 32 * 2, entities[4]));
				break;
			}

			case (7):
			{
				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 8, entities[0]));
				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 6, entities[1]));
				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 4, entities[0]));
				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 10, entities[1]));
				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 12, entities[0]));

				tiles.push_back(Tile(24 + 32 * 6, 24 + 32 * 4, entities[1]));
				tiles.push_back(Tile(24 + 32 * 8, 24 + 32 * 4, entities[0]));
				tiles.push_back(Tile(24 + 32 * 10, 24 + 32 * 4, entities[1]));
				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 4, entities[0]));

				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 6, entities[1]));
				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 8, entities[0]));
				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 10, entities[1]));
				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 12, entities[0]));

				tiles.push_back(Tile(24 + 32 * 6, 24 + 32 * 12, entities[1]));
				tiles.push_back(Tile(24 + 32 * 8, 24 + 32 * 12, entities[0]));
				tiles.push_back(Tile(24 + 32 * 10, 24 + 32 * 12, entities[1]));

				tiles.push_back(Tile(24 + 32 * 6, 24 + 32 * 2, entities[0]));
				tiles.push_back(Tile(24 + 32 * 8, 24 + 32 * 0, entities[1]));
				tiles.push_back(Tile(24 + 32 * 10, 24 + 32 * 2, entities[0]));

				tiles.push_back(Tile(24 + 32 * 6, 24 + 32 * 10, entities[0]));
				tiles.push_back(Tile(24 + 32 * 6, 24 + 32 * 8, entities[1]));
				tiles.push_back(Tile(24 + 32 * 8, 24 + 32 * 8, entities[0]));
				tiles.push_back(Tile(24 + 32 * 10, 24 + 32 * 8, entities[1]));
				tiles.push_back(Tile(24 + 32 * 10, 24 + 32 * 10, entities[0]));

				tiles.push_back(Tile(24 + 32 * 3, 24 + 32 * 2, entities[0]));
				tiles.push_back(Tile(24 + 32 * 3, 24 + 32 * 4, entities[0]));
				tiles.push_back(Tile(24 + 32 * 3, 24 + 32 * 6, entities[0]));
				tiles.push_back(Tile(24 + 32 * 3, 24 + 32 * 8, entities[0]));
				tiles.push_back(Tile(24 + 32 * 3, 24 + 32 * 10, entities[0]));

				tiles.push_back(Tile(24 + 32 * 9, 24 + 32 * 2, entities[1]));
				tiles.push_back(Tile(24 + 32 * 9, 24 + 32 * 4, entities[1]));
				tiles.push_back(Tile(24 + 32 * 9, 24 + 32 * 6, entities[1]));
				tiles.push_back(Tile(24 + 32 * 9, 24 + 32 * 8, entities[1]));
				tiles.push_back(Tile(24 + 32 * 9, 24 + 32 * 10, entities[1]));

				tiles.push_back(Tile(24 + 32 * 15, 24 + 32 * 2, entities[0]));
				tiles.push_back(Tile(24 + 32 * 15, 24 + 32 * 4, entities[0]));
				tiles.push_back(Tile(24 + 32 * 15, 24 + 32 * 6, entities[0]));
				tiles.push_back(Tile(24 + 32 * 15, 24 + 32 * 8, entities[0]));
				tiles.push_back(Tile(24 + 32 * 15, 24 + 32 * 10, entities[0]));

				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 2, entities[1]));
				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 2, entities[1]));

				tiles.push_back(Tile(24 + 32 * 4, 24 + 32 * 9, entities[1]));
				tiles.push_back(Tile(24 + 32 * 12, 24 + 32 * 9, entities[1]));

				tiles.push_back(Entity(24 + 32 * 9, 24 + 32 * 9, entities[5]));
				tiles.push_back(Entity(24 + 32 * 15, 24 + 32 * 0, entities[4]));
			}
		}
		return tiles;
	}
};
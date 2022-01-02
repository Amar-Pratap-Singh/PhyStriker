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
	Loader(vector<SDL_Texture*> e);
	vector<Entity> load_tiles(int level);
	
};
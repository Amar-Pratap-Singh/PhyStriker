#pragma once
#include"Entity.hpp"

class Tile :public Entity {
public:

	Tile(float x, float y, SDL_Texture* te) :Entity(x, y, te)
	{

	}
};
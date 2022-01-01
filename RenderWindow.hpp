#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.hpp"

class RenderWindow
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int windowHeight;
	int windowWidth;

public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void display();
	void Background(SDL_Texture* bg);
	void rndr(SDL_Rect& wall);
	int h();
	int w();
};
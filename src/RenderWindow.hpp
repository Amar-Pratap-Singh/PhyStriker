#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
		void RenderText(SDL_Surface* surface, SDL_Rect rect);
		void renderArrow(Entity &p_entity, Entity &e, int x, int y, double angle, SDL_Point* center);
		void display();
		void Background(SDL_Texture* bg);
		void rndr(SDL_Rect &wall);
		void DrawRectangle(SDL_Texture *tex, int x, int y, int w, int h);
		int h();
		int w();
};
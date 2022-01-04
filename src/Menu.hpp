#pragma once
#include "Button.hpp"
#include "MouseInput.hpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>

class Menu
{
public:
	Menu(RenderWindow *screen);
	void MenuLoop(TTF_Font* font);
	std::string getWindowType();

private:
	std::string window_type = "Main_Menu";
	bool Quit;
	RenderWindow *window;
	SDL_Texture *screen;
	Button *play;
	Button *exit;
	Button *TopScores;
	SDL_Event Events;
};

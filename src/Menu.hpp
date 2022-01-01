#pragma once
#include "Button.hpp"
#include "MouseInput.hpp"
#include <iostream>

class Menu
{
public:
	Menu(RenderWindow *screen);
	void MenuLoop();
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

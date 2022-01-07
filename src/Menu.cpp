#include "Menu.hpp"

Menu :: Menu(RenderWindow* screen){
	window = screen;
}

void Menu::MenuLoop(TTF_Font* font) {
	Quit = false;

	screen = window->loadTexture("images/menu.png");
	play = new Button(window->w()-100, 60, 100, 100, "images/play.png");
	TopScores = new Button(window->w()-100, 150, 100, 50, "images/HighScore2.png");
	exit = new Button(window->w()-100, 200, 100, 50, "images/exit.png");

	MouseInput* mouse = new MouseInput();
 
	bool Main_Menu = true;
	bool Play_Screen = false;

	while (!Quit) {
		
		while (SDL_PollEvent(&Events)) {
			if (Events.type == SDL_QUIT) {
				Quit = true;
			}
		}

		if (Main_Menu) {
			window->clear();        
			
			SDL_Surface* PHYStriker = TTF_RenderText_Solid(font, "PhyStriker", {255, 255, 255});
			SDL_Rect rect = {0, 650, 150, 50};

 			SDL_PumpEvents();
			window->Background(screen);
			play->DrawButton(window);
			exit->DrawButton(window);
			TopScores->DrawButton(window);
			window->RenderText(PHYStriker, rect);

			if (play->isButtonClicked(mouse)) {
				Main_Menu = false;
				Play_Screen = true;
				window_type = "Game";
				break;
			}

			if (exit->isButtonClicked(mouse)) {
				window_type = "Exit";
				break;
			}

			if (TopScores->isButtonClicked(mouse)){
				window_type = "Scores";
				break;
			}

			window->display();
		}
	}
}

std::string Menu::getWindowType() {
	return window_type;
}
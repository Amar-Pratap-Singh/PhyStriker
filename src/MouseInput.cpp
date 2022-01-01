#include "MouseInput.hpp"
#include <SDL2/SDL.h>
#include <vector>

std::vector<int> MouseInput::getMouseCoordinate()
{
	std::vector<int> coordinate;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	coordinate.push_back(mouse_x);
	coordinate.push_back(mouse_y);

	return coordinate;
}

bool MouseInput::checkClick()
{
	SDL_PumpEvents();

	Uint32 buttons;
	buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	if ((buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0)
	{
		return true;
	}
	else
		return false;
}
#include "MouseInput.hpp"
#include <SDL2/SDL.h>

int MouseInput::get_mouse_x()
{
	SDL_GetMouseState(&mouse_x, &mouse_y);
	return mouse_x;
}

int MouseInput::get_mouse_y()
{
	SDL_GetMouseState(&mouse_x, &mouse_y);
	return mouse_y;
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
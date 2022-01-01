#include "Button.hpp"

Button::Button(int x, int y, int w, int h, const char* image) {
	x_pos = x;
	y_pos = y;
	width = w;
	height = h;
	image_path = image;
}

void Button::DrawButton(RenderWindow* window) {
	SDL_Texture* button = window->loadTexture(image_path);
	window->DrawRectangle(button, x_pos, y_pos, width, height);
}

bool Button::isButtonClicked(MouseInput* mouse) {
	std::vector<int> coordinate = mouse->getMouseCoordinate();
	int mouse_x = coordinate[0];
	int mouse_y = coordinate[1];

	int flag = 0;

	if ((mouse_x > x_pos) && (mouse_x < x_pos + width) && (mouse_y > y_pos) && (mouse_y < y_pos + height))
		flag = 1;

	if ((flag == 1) && (mouse->checkClick() == true))
		return true;

	return false;
}
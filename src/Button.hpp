#pragma once
#include "RenderWindow.hpp"
#include "MouseInput.hpp"

class Button {
private:
	int x_pos;
	int y_pos;
	int width;
	int height;
	const char* image_path;

public:
	Button(int x, int y, int w, int h, const char* image);
	void DrawButton(RenderWindow* window);
	bool isButtonClicked(MouseInput* mouse);
};

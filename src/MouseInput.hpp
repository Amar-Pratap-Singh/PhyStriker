#pragma once
// #include <inttypes.h>

class MouseInput {
private:
	int mouse_x;
	int mouse_y;

public:
	int get_mouse_x();
	int get_mouse_y();
	bool checkClick();
};

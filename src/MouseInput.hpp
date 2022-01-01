#pragma once
#include<iostream>
#include <vector>

class MouseInput {
private:
	int mouse_x;
	int mouse_y;

public:
	std::vector<int> getMouseCoordinate();
	bool checkClick();
};
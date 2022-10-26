#pragma once

#include "Drawable.hpp"

class Apple : public Drawable {
	bool eaten = false;
	public:
		Apple(Point position, int width) : Drawable(position, Point(width, width), 0,  Rectangle(Point(167, 7), Point(38, 38))) {};
		void eat();
		void respond(int framerate);
};
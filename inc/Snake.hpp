#pragma once
#include <pspctrl.h>
#include <deque>

#include "DrawingInterface.hpp"
#include "Drawable.hpp"
#include "Point.hpp"

extern char CUSTOM_DEBUG_INFO[100];

struct snake_element {
	Point position;
	float direction;
	snake_element(Point position, float direction);
};

class Snake {
	private:
		Drawable *head, *tail;
		std::deque <snake_element> body;
		float speed, direction, width;
		Point position;
		int to_add;
	public:
		Snake();
		void draw(DrawingInterface*);
		void respond(SceCtrlData, float framerate);
		void add_lenght(int count=1);
		Drawable get_head() {return *head;}
};
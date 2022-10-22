#pragma once
#include <pspctrl.h>

#include "DrawingInterface.hpp"
#include "Point.hpp"

class Snake {
	private:
		int lenght;
		float speed, direction;
		Point position;
	public:
		Snake();
		void draw(DrawingInterface*);
		void respond(SceCtrlData, float framerate);
};
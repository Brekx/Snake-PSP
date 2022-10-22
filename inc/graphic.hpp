#pragma once

#include "Rectangle.hpp"
#include "DrawingInterface.hpp"

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

class Graphic : public DrawingInterface {
	public:
		void init();
		void beginDraw();
		void endDraw();
		void drawImageFromTex(Rectangle location, Rectangle tex_location);
		void drawRectangle(Rectangle rectangle, unsigned int color);
		void terminate();
};
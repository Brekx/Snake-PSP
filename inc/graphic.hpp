#pragma once

#include "Rectangle.hpp"
#include "DrawingInterface.hpp"

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

class Graphic : public DrawingInterface {
	private:
		float framerate;
		u64 clock;
	public:
		void init();
		void beginDraw();
		void endDraw();
		void drawImageFromTex(Rectangle location, Rectangle tex_location);
		void drawRectangle(Rectangle rectangle, unsigned int color);
		void drawPolygon(Point *point, int count, unsigned int color);
		void terminate();
		float getFramerate();
};
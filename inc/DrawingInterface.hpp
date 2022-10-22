#pragma once

#include "Rectangle.hpp"

class DrawingInterface {
	public:
		virtual void drawImageFromTex(Rectangle location, Rectangle tex_location) = 0;
		virtual void drawRectangle(Rectangle rectangle, unsigned int color);
};
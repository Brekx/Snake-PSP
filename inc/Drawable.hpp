#pragma once

#define PI 3.14159265358979

#include <math.h>

#include "Point.hpp"
#include "Rectangle.hpp"
#include "DrawingInterface.hpp"


class Drawable {
	public:
		Point position, size;
		float rotation;
		Rectangle texture;

		Drawable(Point position, Point size, float rotation, Rectangle texture);
		void draw(DrawingInterface *g);

		void resize(Point size) {
			this->size = size;
		}

		void move(Point position) {
			this->position = position;
		}

		void rotate(float rotation) {
			this->rotation = rotation;
		}

		bool do_collide(Drawable);
};
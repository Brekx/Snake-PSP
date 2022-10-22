#pragma once

#define PI 3.14159265358979

#include <math.h>

#include "Point.hpp"
#include "Rectangle.hpp"
#include "DrawingInterface.hpp"


struct Object {
	Point position, size;
	float rotation;
	Rectangle texture;

	public:
		Object(Point position, Point size, float rotation, Rectangle texture) {
			this->position = position;
			this->size = size;
			this->rotation = rotation;
			this->texture = texture;
		}
		
		void draw(DrawingInterface *g) {
			Rectangle tmp_position = {position, position, position, position};
			float s = sinf(rotation*2*PI), c = cosf(rotation*2*PI);
			float cx = size.x/2, cy = size.y/2;
			tmp_position.p1.x += -cx*c + cy*s;
			tmp_position.p2.x += cx*c + cy*s;
			tmp_position.p3.x += cx*c - cy*s;
			tmp_position.p4.x += -cx*c - cy*s;
			
			tmp_position.p1.y += -cy*c - cx*s;
			tmp_position.p2.y += -cy*c + cx*s;
			tmp_position.p3.y += cy*c + cx*s;
			tmp_position.p4.y += cy*c - cx*s;
			g->drawImageFromTex(tmp_position, texture);
		}

		void setRotation(float rotation) {
			this->rotation = rotation;
		}

		float getRotation() {
			return rotation;
		}

		void move(float v) {
			float s = sinf(rotation*2*PI), c = cosf(rotation*2*PI);
			position.x += v*s;
			position.y -= v*c;
		}

		Point getPosition() {
			return position;
		}
};
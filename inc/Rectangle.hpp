#pragma once

#include "Point.hpp"

struct Rectangle {
	Point p1, p2, p3, p4;
	Rectangle() {
		
	}
	Rectangle(Point p1, Point p2, Point p3, Point p4) {
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
		this->p4 = p4;
	}
	Rectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
		p1 = Point(x1, y1);
		p2 = Point(x2, y2);
		p3 = Point(x3, y3);
		p4 = Point(x4, y4);
	}
};
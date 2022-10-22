#include <cmath>

#include "Snake.hpp"

#define M_PI		3.14159265358979323846

Snake::Snake() {
	speed = .5f;
	position = Point(200, 100);
	direction = M_PI/4;
	lenght = 1;
}
void Snake::draw(DrawingInterface* g) {
	g->drawRectangle(Rectangle(position, Point(10, 10)), 0xFF0000FF);
}
void Snake::respond(SceCtrlData pad, float framerate) {
	if(pow(pad.Lx-127, 2)+pow(pad.Ly-127, 2) > 2500) {
		direction = atan2f(pad.Lx-127, pad.Ly-127);// + pad.Ly>127 ? 2*M_PI : 0;
	}

	float dx=0, dy=0;
	dx = sinf(direction) * speed;
	dy = cosf(direction) * speed;

	if(position.x + dx > 0 && position.x + dx < 470)
		position.x += dx;
	if(position.y + dy > 0 && position.y + dy < 470)
		position.y += dy;
}
#include <cmath>
#include <cstdio>

#include "Snake.hpp"

#define M_PI		3.14159265358979323846

snake_element::snake_element(Point position, float direction) {
	this->position = position;
	this->direction = direction;
}

Snake::Snake() {
	width = 20;
	body = std::deque<snake_element>();
	to_add = 20;
	speed = .5f;
	position = Point(200, 100);
	direction = 0;
	head = new Drawable(Point(200, 100), Point(2*width, 2*width), direction, Rectangle(Point(0, 0), Point(59, 53)));
	tail = new Drawable(Point(100, 100), Point(2*width, 2*width), direction, Rectangle(Point(59, 0), Point(107, 60)));
}

void Snake::draw(DrawingInterface* g) {
	snake_element prev = {position, direction};
	for(int i=0; i<body.size(); i++) {
		Rectangle a;
		a.p1.x = cosf(prev.direction-M_PI/2)*width+prev.position.x;
		a.p1.y = sinf(prev.direction-M_PI/2)*width+prev.position.y;
		a.p2.x = cosf(prev.direction+M_PI/2)*width+prev.position.x;
		a.p2.y = sinf(prev.direction+M_PI/2)*width+prev.position.y;
		a.p3.x = cosf(body[i].direction+M_PI/2)*width+body[i].position.x;
		a.p3.y = sinf(body[i].direction+M_PI/2)*width+body[i].position.y;
		a.p4.x = cosf(body[i].direction-M_PI/2)*width+body[i].position.x;
		a.p4.y = sinf(body[i].direction-M_PI/2)*width+body[i].position.y;
		g->drawRectangle(a, 0xff00ff00);
		prev = body[i];
	}
	head->move(position);
	head->rotate(direction);
	head->draw(g);
	tail->draw(g);
}

void Snake::add_lenght(int count) {
	to_add+=count;
}

void Snake::respond(SceCtrlData pad, float framerate) {
	if(pow(body.front().position.x-position.x, 2)+pow(body.front().position.y-position.y, 2)>pow(width, 2)) {
		if(to_add<=0)
			body.pop_back();
		else
			to_add--;
		body.push_front(snake_element(position, direction));
	}
	
	if(pow(pad.Lx-127, 2)+pow(pad.Ly-127, 2) > 2500)
		if(pad.Lx>127)
			direction += M_PI/framerate;
		else
			direction -= M_PI/framerate;

	float dx=0, dy=0;
	dx = cosf(direction) * speed;
	dy = sinf(direction) * speed;

	if(position.x + dx > 0 && position.x + dx < 471)
		position.x += dx;
	if(position.y + dy > 0 && position.y + dy < 262)
		position.y += dy;
	dx = body.back().position.x - tail->position.x;
	dy = body.back().position.y - tail->position.y;
	float r = sqrt(pow(dx, 2)+pow(dy, 2));
	if(r>5*width)
		r = 1;
	else
		r = sinf(r/(5*width)*M_PI/2);
	tail->rotation = atan2f(dy, dx) + PI;
	tail->position.x -= cosf(tail->rotation)*3*speed*sinf(r);
	tail->position.y -= sinf(tail->rotation)*3*speed*sinf(r);
}
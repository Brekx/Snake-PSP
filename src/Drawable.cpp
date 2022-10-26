#include "Drawable.hpp"

Drawable::Drawable(Point position, Point size, float rotation, Rectangle texture) {
	this->position = position;
	this->size = size;
	this->rotation = rotation;
	this->texture = texture;
}

void Drawable::draw(DrawingInterface *g) {
	Rectangle tmp_position = {position, position, position, position};
	float s = sinf(rotation), c = cosf(rotation);
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

bool Drawable::do_collide(Drawable obj) {
	for(int i=0; i<4; i++) {
		Point p = Point(obj.position.x+(i==2||i==3 ? obj.size.x : 0), obj.position.y+(i==3||i==4 ? obj.size.y : 0));
		if(p.x>position.x && p.x<position.x+size.x && p.y > position.y && p.y < position.y+size.y)
			return true;
	}
	return false;
}
#include "Apple.hpp"

void Apple::eat() {
	eaten = true;
}

void Apple::respond(int framerate) {
	if(eaten) {
		rotation += 12*PI/framerate;
		size.x -= size.x*30*PI/framerate;
		size.y -= size.y*30*PI/framerate;
	}
	// if(rotation>4*PI)
	// 	delete(this);
}
#include "Borderlayout.h"



Borderlayout::Borderlayout() : north(), east(), south(), west(), center() {}

void Borderlayout::add(LayoutDirection const& dir, IDrawable const& drawable) {
	switch (dir) {
		case NORTH:
			north.push_back(drawable);
		case EAST:
			east.push_back(drawable);
		case SOUTH:
			south.push_back(drawable);
		case WEST:
			west.push_back(drawable);
		case CENTER:
			center.push_back(drawable);
		default:
			break;
	}
}

Borderlayout::~Borderlayout() {}

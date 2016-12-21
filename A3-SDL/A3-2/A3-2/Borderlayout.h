#include "IDrawable.h"
#include <functional>
#include <tuple>
#include <vector>

#pragma once

using namespace std;

enum LayoutDirection { NORTH, EAST, SOUTH, WEST, CENTER };

class Borderlayout : IDrawable {
	private:
	// Following a few reserved vectors for having 
	vector<IDrawable> north;
	vector<IDrawable> east;
	vector<IDrawable> south;
	vector<IDrawable> west;
	vector<IDrawable> center;
	public:
	Borderlayout();
	void add(LayoutDirection const&, IDrawable const&);
	~Borderlayout();
};

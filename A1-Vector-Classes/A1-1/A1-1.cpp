// A1-1.cpp : Defines the entry point for the console application.
//

// #include "test11.h"
#include "Vec3f.h"
#include <iostream>
#include <string>

int main()
{
	const my::Vec3f x(1, 2, 3);
	auto f = x[1];
	my::Vec3f y(1, 2, 3);
	my::Vec3f z(1, 4, 3);
	y[1] = 4;
	std::cout << f << std::endl;
	std::cout << y[1] << std::endl;
	std::cout << std::to_string(y == z) << std::endl;
	y += y;
	std::cout << y[0] << std::endl;
}

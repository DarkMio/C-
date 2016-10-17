// A1-1.cpp : Defines the entry point for the console application.
//

// #include "test11.h"
#include "Vec3f.h"
#include "test11.h"
#include <iostream>
#include <string>

int main()
{
/*
	my::Vec3f x(1, 2, 3);
	auto f = x[1];
	my::Vec3f y(1, 2, 3);
	my::Vec3f z(1, 4, 3);

	y[1] = 4;
	std::cout << f << std::endl;
	std::cout << y[1] << std::endl;
	std::cout << std::to_string(y == z) << std::endl;
	y += y;
	std::cout << y << std::endl;

	auto b = my::Vec3f(1, 2, 3) + my::Vec3f(1, 1, 1);
	std::cout << b << std::endl;

	my::Vec3f a;	a += x += y;
	std::cout << a << std::endl;
*/
	my::Vec3f x(1, 2, 3);	my::Vec3f y(1, 1, 1);	auto z = x + y;	std::cout << x << std::endl;	std::cout << y << std::endl;	std::cout << z << std::endl;
	std::cout << -z << std::endl;
	test_Vec3f();
}

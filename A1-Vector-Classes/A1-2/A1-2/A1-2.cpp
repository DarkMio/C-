// A1-2.cpp : Defines the entry point for the console application.
//
#include <array>
#include "Vec.h"
#include <iostream>
#include "test11.h"

int main()
{
	test_Vec();
	my::Vec<float, 3> f({ 1, 2, 3 });
	my::Vec<float, 4> h({ 1, 2, 3, 4 });
	my::Vec<float, 3> g({ 1, 2, 4 });
	my::Vec<float, 3> j({ 1, 2, 3 });
	std::cout << (f == g) << std::endl;
	std::cout << (f == j) << std::endl;
	std::cout << (f == my::Vec<float, 3>({ 1, 2, 3 })) << std::endl;
	std::cout << f << std::endl;
	std::cout << (-f) << std::endl;
	std::cout << (f + j) << std::endl;
	std::cout << (f - j) << std::endl;

	f += j;
	std::cout << f << std::endl;
	std::cout << dot(j, j) << std::endl;
	std::cout << dot(h, h) << std::endl;
    return 0;
}


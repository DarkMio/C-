// A1-3.cpp : Defines the entry point for the console application.
//
#include "Mat.h"
#include <array>
#include <iostream>
#include "util.h"
#include <string>
#include "test_driver.h"

int main()
{
	/*
	my::Vec<float, 3> a({ 1, 2, 3 });
	my::Vec<float, 3> b({ 4, 5, 6 });
	my::Vec<float, 3> c({ 7, 8, 9 });
	my::Mat<float, 3> d({ a, b, c });
	std::cout << d[2] << std::endl;
	std::cout << to_string(d, 6, 2) << std::endl;
	std::cout << "  Identity:" << std::endl;
	std::cout << d.identity() << std::endl;
	my::Mat<float, 3> ident(d.identity()); // redundant, but works!
	my::Mat<float, 3> thing({
		my::Vec<float, 3>({2, 0, 0}),
		my::Vec<float, 3>({0, 2, 0}),
		my::Vec<float, 3>({0, 0, 2})
	});
	my::Vec<float, 3> x = thing * a;
	std::cout << "  Mat x Vec:\n" << to_string(x) << std::endl;
	my::Mat<int, 2> lhs({
		my::Vec<int, 2>({1, 3}),
		my::Vec<int, 2>({2, 4})
	});
	my::Mat<int, 2> rhs({
		my::Vec<int, 2>({2, 1}),
		my::Vec<int, 2>({0, 2})
	});
	my::Mat<int, 2> result = lhs * rhs;
	std::cout << "  Mat x Mat" << std::endl;
	std::cout << to_string(result, 6, 2) << std::endl;
	std::cout << to_string(result, 3, 0) << std::endl;
	*/

	test_mat();
    return 0;
}


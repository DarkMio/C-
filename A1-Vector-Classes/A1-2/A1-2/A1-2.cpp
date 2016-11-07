// A1-2.cpp : Defines the entry point for the console application.
//
#include <array>
#include "Vec.h"
#include <iostream>
#include "test11.h"

int main()
{
	test_Vec();
	test_vec_generic<int, 2>();
	test_vec_generic<double, 4>();
	test_vec_generic<float, 3>();
	// test_vec_generic<bool, 1>(); // actually works, but causes a lot of compiler warnings
    return 0;
}


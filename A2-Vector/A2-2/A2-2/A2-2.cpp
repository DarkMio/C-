// A2-2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "test_generic.h"
#include "test21.h"
#include <iostream>


int main()
{
	test_21();
	test_generic<int>();
	test_payload();

    return 0;
}
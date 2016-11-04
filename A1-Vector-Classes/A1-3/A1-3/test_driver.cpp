#include "test_driver.h"
#include "Mat.h"
#include <array>
#include <assert.h>
#include <iostream>

using namespace my;
using namespace std;

void test_mat() {
	Vec<float, 4> matArray1({ 1, 5, 9,  13 });
	Vec<float, 4> matArray2({ 2, 6, 10, 14 });
	Vec<float, 4> matArray3({ 3, 7, 11, 15 });
	Vec<float, 4> matArray4({ 4, 8, 12, 16 });
	Mat<float, 4> incrementMat({ matArray1, matArray2, matArray3, matArray4 });
	Mat<float, 4> identity4x4({
		Vec<float, 4>({ 1, 0, 0, 0 }),
		Vec<float, 4>({ 0, 1, 0, 0 }),
		Vec<float, 4>({ 0, 0, 1, 0 }),
		Vec<float, 4>({ 0, 0, 0, 1 }),
	});
	{
		cout << "Testing Matrixes in different types and sizes..." << endl << endl;
		cout << "  Identity generation: ";
		assert(incrementMat.identity() == identity4x4);
		Mat<float, 4> identMult = incrementMat * incrementMat.identity();
		cout << endl << identMult << endl;
		assert(identMult[0] == matArray1);
		assert(identMult[1] == matArray2);
		assert(identMult[2] == matArray3);
		assert(identMult[3] == matArray4);
		cout << "passed." << endl;

	}
}

void test_vec() {}
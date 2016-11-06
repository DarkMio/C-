#include "test_driver.h"
#include "util.h"
#include "Mat.h"
#include <array>
#include <assert.h>
#include <iostream>

using namespace my;
using namespace std;

void test_mat() {
	test_vec_generic<float, 4>(); // first we make sure that the vector functions properly
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

	cout << "================================================" << endl;
	cout << "Testing Matrixes in different types and sizes..." << endl;
	cout << "================================================" << endl;

	{
		cout << "  Matrix equality: ";
		assert(incrementMat == incrementMat);
		assert(!(incrementMat != incrementMat));
		assert(!(incrementMat == identity4x4));
		assert(incrementMat != identity4x4);
		cout << "passed." << endl;
	}

	{
		cout << "  Matrix access: ";
		assert(incrementMat[0] == matArray1);
		assert(incrementMat[1] == matArray2);
		assert(incrementMat[2] == matArray3);
		assert(incrementMat[3] == matArray4);
		cout << "passed." << endl;
	}

	{
		cout << "  Identity generation: ";
		assert(incrementMat.identity() == identity4x4);
		Mat<float, 4> identMult = incrementMat * incrementMat.identity();
		// cout << endl << identMult << endl;
		assert(identMult[0] == matArray1);
		assert(identMult[1] == matArray2);
		assert(identMult[2] == matArray3);
		assert(identMult[3] == matArray4);
		cout << "passed." << endl;
	}

	{
		cout << "  Matrix constness: ";
		const Mat<float, 4> a = incrementMat;
		const Mat<float, 4> b = a * incrementMat.identity();
		const Mat<float, 4> c = a.identity() * a;
		// mathematical induction: a == c
		assert(a == b);
		assert(b == c);
		cout << "  passed." << endl;
	}

	{
		cout << "  Matrix x Vector calculation: ";
		assert((incrementMat * matArray1 == Vec<float, 4>({ 90, 202, 314, 426 })));
		assert((incrementMat * matArray2 == Vec<float, 4>({ 100, 228, 356, 484 })));
		assert((incrementMat * matArray3 == Vec<float, 4>({ 110, 254, 398, 542 })));
		assert((incrementMat * matArray4 == Vec<float, 4>({ 120, 280, 440, 600 })));
		cout << "passed." << endl;
	}

	{
		cout << "  Matrix x Matrix calculation: ";
		Mat<float, 4> a({
			Vec<float, 4>({90, 202, 314, 426}),
			Vec<float, 4>({100, 228, 356, 484}),
			Vec<float, 4>({110, 254, 398, 542}),
			Vec<float, 4>({120, 280, 440, 600})
		});
		assert(incrementMat * incrementMat == a);
		Mat<float, 4> b({
			Vec<float, 4>({ 3140, 7268, 11396, 15524 }),
			Vec<float, 4>({ 3560, 8232, 12904, 17576 }),
			Vec<float, 4>({ 3980, 9196, 14412, 19628 }),
			Vec<float, 4>({ 4400, 10160, 15920, 21680 })
		});
		assert(incrementMat * a == b);
		cout << "passed." << endl;
		cout << "  Print Tests:" << endl << "______________________________________" << endl;
		cout << to_string(incrementMat) << endl << to_string(a, 8, 2) << endl << to_string(b, 7, 0) << endl;
	}
	cout << "______________________________________" << endl << "all Mat<float, 4> tests passed." << endl << endl;
}
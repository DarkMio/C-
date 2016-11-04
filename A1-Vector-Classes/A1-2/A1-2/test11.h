#pragma once
#include <iostream>
#include <array>
#include <assert.h>
#include "Vec.h"

using namespace std;
using namespace my;

void test_Vec();

template<typename T, int N>
inline void test_vec_generic() {
#ifndef NDEBUG

	// Builds {0, 1, ..., N} arrays
	auto build_values = [](int size) {
		std::array<T, N> values{};
		for (int i = 0; i < N; i++) {
			values[i] = (T) i;
		}
		return values;
	};

	auto continous_generation = [](int size) {
		static int callCount = 0;
		std::array<T, N> values{};
		for (int i = callCount * N; i < N * (callCount + 1); i++) {
			values[i % N] = (T)i;
		}
		callCount++;
		return values;
	};

	cout << "=======================" << endl;
	cout << " Testing Vec<" << typeid(T).name() << ", " << N << "> " << endl;
	cout << "=======================" << endl;

	
	{
		cout << "  value type and dimension:";
		assert(typeid(Vec<T, N>::value_type).name() == typeid(T).name());
		assert((Vec<T, N>::dimension == N));
		cout << "passed." << endl;
	}

	{
		// do not tolerate any memory overhead
		cout << "  sizeof(Vec<float, 3>) == 3 bytes: ";
		assert(sizeof(Vec<T, N>) == N * sizeof(T));
		cout << "passed." << endl;
	}

	{
		cout << "  constructor & index operator: ";
		Vec<T, N> a;
		// build up a value array and construct a vector
		Vec<T, N> b(build_values(N));
		for (int i = 0; i < N; i++) {
			assert(a[i] == 0);
			assert(b[i] == i);
		}
		cout << "passed." << endl;
	}

	{
		cout << "  read-only access to const object: ";
		const std::array<T, N> values = build_values(N);
		const Vec<T, N> a(values);
		// the next line will throw a compiler error if there is no proper "operator[] const"
		if (N > 0) {
			assert(a[0] == values[0]);
		}
		cout << "passed." << endl;
	}

	{
		cout << "  write access to a non-const object: ";
		const std::array<T, N> values = build_values(N);
		Vec<T, N> a(values);
		if (N > 0) {
			a[0] = 4;
			assert(a[0] == 4);
			for (int i = 1; i < N; i++) {
				assert(a[i] == values[i]);
			}
		}
		cout << "passed." << endl;
	}

	{
		cout << "  comparison: ";
		const std::array<T, N> values = build_values(N);
		Vec<T, N> a(values), b(values), c(continous_generation(N)), d(continous_generation(N));
		d += d;
		if (N > 0) {
			c[0] = 9;
		}
		assert(a == b);
		assert(a == a);
		assert(a != c);
		assert(b != d);
		assert(!(a != b));
		cout << "passed." << endl;
	}

	{
		// should work out of the box when using std container (!)
		cout << "  assignment: ";
		Vec<T, N> a(build_values(N)), b(continous_generation(N));
		cout << a[0] << " "; // to make sure these values are not optimized away! 
		a = b;
		for (int i = 0; i < N; i++) {
			assert(a[i] == b[i]);
		}
		cout << "passed." << endl;
	}
	
	{
		cout << "  addition:";
		Vec<T, N> a(continous_generation(N));
		Vec<T, N>  b({});
		for (int i = 0; i < N; i++) {
			b[i] = N;
		}
		a += b;
		std::array<T, N> n = continous_generation(N);
		assert((a == Vec<T, N>(n)));
		
		/*
		auto c = a + Vec<float, 3>({ 1,1,1 });
		assert((c == Vec<float, 3>({ 6, 8, 10 })));
		Vec<float, 3> one({ 1,1,1 }), four({ 4, 4, 4 });
		one += one + one + one;
		assert(one == four);
		Vec<float, 3> x({ 0,0,0 }), y({ 1, 1, 1 }), z({ 2, 2, 2 });
		x += y += z;
		assert((y == Vec<float, 3>({ 3,3,3 })));
		assert(x == y);
		*/
		cout << "passed." << endl;
	}

	{
		cout << "  unary minus: ";
		array<T, N> values = continous_generation(N);
		array<T, N> valuesNegated{};
		for (int i = 0; i < N; i++) {
			valuesNegated[i] = -values[i];
		}
		Vec<T, N> a(values), b(valuesNegated);
		assert(-a == b);
		cout << "passed." << endl;
	}


	/*
	{
	cout << "  dot product: ";
	Vec<float, 3> a({ 1,2,3 });
	assert(dot(a, a) == 1 * 1 + 2 * 2 + 3 * 3);
	cout << "passed." << endl;
	}

	{
	// these tests will not compile if you forgot to declare
	// some methods const
	cout << "  constness: ";
	const Vec<float, 3> a({ 1,2,3 });
	assert(a[1] == 2);
	assert(a == a);
	assert(!(a != a));
	assert((a + a == Vec<float, 3>({ 2,4,6 })));
	assert((-a == Vec<float, 3>({ -1, -2, -3 })));
	assert(dot(a, a) == 1 * 1 + 2 * 2 + 3 * 3);
	cout << "passed." << endl;
	}

	cout << "all Vec<float, 3> tests passed." << endl << endl;
	
	*/
#endif
}

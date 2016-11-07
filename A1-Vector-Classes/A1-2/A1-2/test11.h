#pragma once
#include <iostream>
#include <array>
#include <assert.h>
#include <sstream>
#include <string>
#include "Vec.h"

using namespace std;
using namespace my;

void test_Vec();

template<typename T, int N>
inline void test_vec_generic() {
#ifndef NDEBUG
	static_assert(N > 0, "Cannot run tests on zero or less vector sizes.");
	// Builds {0, 1, ..., N} arrays
	auto build_values = []() {
		std::array<T, N> values{};
		for (int i = 0; i < N; i++) {
			values[i] = (T) i;
		}
		return values;
	};

	// Builds {N-size, ..., N-1, N} arrays, going onward N steps with each generation
	auto continous_generation = []() {
		static int callCount = 0;
		std::array<T, N> values{};
		for (int i = callCount * N; i < N * (callCount + 1); i++) {
		#pragma warning(suppress:4724) // potential mod by 0 - can't be, otherwise loop would yield 0 iterations
			values[i % N] = (T)i;
		}
		callCount++;
		return values;
	};

	cout << "================================" << endl;
	cout << " Testing " << typeid(Vec<T, N>).name() << endl;
	cout << "================================" << endl;
	
	{
		cout << "  value type and dimension:";
		assert(typeid(Vec<T, N>::value_type).name() == typeid(T).name());
		assert((Vec<T, N>::dimension == N));
		cout << "passed." << endl;
	}

	{
		// do not tolerate any memory overhead
		auto size = N * sizeof(T);
		cout << "  sizeof(" << typeid(Vec<T, N>).name() << ") == " << size << " bytes: ";
		assert(sizeof(Vec<T, N>) == size);
		cout << "passed." << endl;
	}

	{
		cout << "  constructor & index operator: ";
		Vec<T, N> a;
		// build up a value array and construct a vector
		Vec<T, N> b(build_values());
		for (int i = 0; i < N; i++) {
			assert(a[i] == 0);
			assert(b[i] == i);
		}
		cout << "passed." << endl;
	}

	{
		cout << "  read-only access to const object: ";
		const std::array<T, N> values = build_values();
		const Vec<T, N> a(values);
	#pragma warning(suppress:4127) // conditional expression is constant
		if (N > 0) {
			// the next line will throw a compiler error if there is no proper "operator[] const"
			assert(a[0] == values[0]);
		}
		cout << "passed." << endl;
	}

	{
		cout << "  write access to a non-const object: ";
		const std::array<T, N> values = build_values();
		Vec<T, N> a(values);
	#pragma warning(suppress:4127) // conditional expression is constant
		if (N > 0) {
			// overwrite a[0] to a casted value of 4
			a[0] = (T) 4;
			// check the overwritten value
			assert(a[0] == (T) 4);
			for (int i = 1; i < N; i++) {
				// check the rest
				assert(a[i] == values[i]);
			}
		}
		cout << "passed." << endl;
	}

	{
		cout << "  comparison: ";
		const std::array<T, N> values = build_values();
		// use generated values and then get some more values counted up from there
		Vec<T, N> a(values), b(values), c(continous_generation()), d(continous_generation());
		d += d;
	#pragma warning(suppress:4127) // conditional expression is constant
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
		// a has {0, ..., N} and b has then randomly starting, but continous values
		Vec<T, N> a(build_values()), b(continous_generation());
	#pragma warning(suppress:4127) // conditional expression is constant
		if (N > 0) {
			cout << a[0] << " "; // to make sure these values are not optimized away! 
		}
		a = b;
		// then check all values
		for (int i = 0; i < N; i++) {
			assert(a[i] == b[i]);
		}
		cout << "passed." << endl;
	}
	
	{
		cout << "  addition:";
		Vec<T, N> a(continous_generation());
		Vec<T, N>  b;
		// b being {N, ..., N} makes the following addition jumping the values up - 
		// which then would be exactly the same as calling a next continous generation.
		for (int i = 0; i < N; i++) {
			b[i] = N;
		}
		a += b;
		std::array<T, N> n = continous_generation();
		assert((a == Vec<T, N>(n)));
		cout << "passed." << endl;
	}

	{
		cout << "  unary minus: ";
		array<T, N> values = continous_generation();
		array<T, N> valuesNegated{}; // @TODO std::transform? Help?
		for (int i = 0; i < N; i++) {
			valuesNegated[i] = -values[i];
		}
		Vec<T, N> a(values), b(valuesNegated);
		assert(-a == b);
		cout << "passed." << endl;
	}

	{
		cout << "  dot product: ";
		auto values = continous_generation();
		Vec<T, N> a(values);
		T sum = (T) 0;
		for (int i = 0; i < N; i++) {
			sum += values[i] * values[i];
		}

		assert(dot(a, a) == sum);
		cout << "passed." << endl;
	}
	
	{
		// these tests will not compile if you forgot to declare
		// some methods const
		cout << "  constness: ";
		const auto values = continous_generation();
		array<T, N> doubleValues{};
		array<T, N> negativeValues{};
		T dotProduct = (T) 0;
		// calculate the double of {values}, the negative of {values} and the dot product.
		for (int i = 0; i < N; i++) {
			doubleValues[i] = values[i] * 2;
			negativeValues[i] = -values[i];
			dotProduct += values[i] * values[i];
		}
		const Vec<T, N> a(values);
	#pragma warning(suppress:4127) // conditional expression is constant
		if (N > 0) {
			assert(a[0] == values[0]);
		}
		assert(a == a);
		assert(!(a != a));
		assert((a + a == Vec<T, N>(doubleValues)));
		assert((-a == Vec<T, N>(negativeValues)));
		assert(dot(a, a) == dotProduct);
		cout << "passed." << endl;
	}

	cout << "all " << typeid(Vec<T, N>).name() << " tests passed." << endl << endl;
#endif
}

#pragma once

#include <iostream>
#include <assert.h>
#include "my_vector.h"
#include "payload.h"

using namespace std;
using namespace my;

void test_payload();

/**
 * Only works with numerical types, thanks.
 */
template<typename T>
void test_generic() {
#pragma warning(disable : 4244) // -> possible loss of data, implicit conversion
	{
		cout << endl << "## Testing my::vector<" << typeid(T).name() << ">" << endl;
	}

	{
		cout << "> Initialization with any constructor: ";
		vector<T> v0;
		vector<T> v1(3);
		vector<T> v2(5, T());
		assert(v0.size() == 0);
		assert(v0.capacity() == 0);
		assert(v1.size() == 0);
		assert(v1.capacity() == 3);
		assert(v2.size() == 1);
		assert(v2.capacity() == 5);
		cout << "DONE." << endl;
	}
	{
		cout << "> Emptiness, Pushing, Popping, Clearing: ";
		vector<T> v0;
		vector<T> v1(1, T());
		assert(v0.empty());
		assert(!v1.empty());
		for (int i = 0; i < 25; i++) {
			v0.push_back(T(i));
			v1.push_back(T(i));
		}
		assert(!v0.empty());
		assert(v0.size() == 25);
		assert(v1.size() == 26);
		v1.clear();
		assert(v1.empty());
		for (int i = 24; i >= 0; i--) {
			assert(v0.pop_back() == T(i));
		}
		assert(v0.empty());
		assert(v0.size() == 0);
		assert(v1.size() == 0);
		cout << "DONE." << endl;
	}
	{
		cout << "> Accessors and Assignments: ";
		vector<T> v0(5, T());
		vector<T> v1(3);
		assert(v0[0] == T());
		assert(v0.at(0) == T());
		v0.push_back(T()); // increments m_size, which should be the normal case.
		v1.push_back(T()); // same here... which makes .at() properly working (due to m_size limitations)
		v0[1] = T(1);
		v1[0] = T(2);
		// still unchanged?
		assert(v0[0] == T());
		// and these changed?
		assert(v0[1] == T(1));
		assert(v1[0] == T(2));
		v0.at(1) = T(3);
		v1.at(0) = T(4);
		// still unchanged?
		assert(v0[0] == T());
		// and these changed?
		assert(v0[1] == T(3));
		assert(v1[0] == T(4));
		cout << "DONE." << endl;
	}
	{
		cout << "> Exceptions in at(): ";
		vector<T> v0;
		bool catched = false;
		try {
			v0.at(1);
		} catch(std::out_of_range e) {
			catched |= true;
		}
		try {
			v0.at(-1);
		} catch(std::out_of_range e) {
			catched &= true;
		}
		assert(catched);
		cout << "DONE." << endl;
	}
	{
		cout << "> Constness: ";
		// There is not really much to do, honestly.
		const vector<T> v0(3, T(3));
		vector<T> v1(1);
		v1[0] = v0[0];
		assert(v0[0] == v1[0]);
		cout << "DONE." << endl;
	}
	{
		cout << "> Reserving, adding, shrinking: ";
		vector<T> v0;
		v0.reserve(25);
		assert(v0.size() == 0);
		assert(v0.capacity() == 25);
		for (int i = 0; i < 25; i++) {
			v0.push_back(T(i));
		}
		assert(v0.size() == 25);
		assert(v0.capacity() == 25);
		v0.push_back(T());
		assert(v0.size() == 26);
		// actually, depending on impl, this could now vary...
		assert(v0.capacity() > 25);
		for (int i = 0; i < 11; i++) {
			v0.pop_back();
		}
		assert(v0.size() == 15);
		assert(v0.capacity() > 25);
		v0.shrink_to_fit();
		assert(v0.size() == 15);
		assert(v0.capacity() == 15);
		cout << "DONE." << endl;
	}
	{
		cout << "> Copy construction: ";
		vector<T> v0(25);
		vector<T> v1(25);
		for (int i = 0; i < 25; i++) {
			v0.push_back(T(i));
			v1.push_back(T(i));
		}
		vector<T> v2(std::move(v0));
		for (int i = 0; i < 25; i++) {
			assert(v1[i] == v2[i]);
		}
		assert(v2.size() == 25);
		cout << "DONE." << endl;
	}
#pragma warning(default : 4244)
}

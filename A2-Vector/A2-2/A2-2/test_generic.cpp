#include <iostream>
#include "my_vector.h"
#include <assert.h>

using namespace std;
using namespace my;

/**
 * Only works with numerical types, thanks.
 */
template<typename T>
void test_generic() {
	{
		cout << "## Testing my::vector<" << typeid(T).name() ">" << endl;
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
		assert(v2.size() == 0);
		assert(v2.capacity() == 5);
		cout << "DONE." << endl;
	}
	{
		cout << "> Accessors and Assignments: ";
		vector<T> v0(5, T());
		vector<T> v1(3);
		assert(v0[0] == T());
		assert(v0.at(0) == T());
		v0[1] = T(1);
		v1[0] = T(2);
		// still unchanged?
		assert(v0[0] == T());
		// and these changed?
		assert(v0[1] == T(1));
		assert(v1[0] == T(2));
		cout << "DONE." << endl;
	}
	{
		cout << "> Constness: ";
		const vector<T> v0(3, T(3));

	}
}
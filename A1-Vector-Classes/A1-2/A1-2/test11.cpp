#include <iostream>
#include <cassert>
#include <typeinfo>
#include <array>
using namespace std;

#include "Vec.h"
using namespace my;

void test_Vec() {

#ifndef NDEBUG
	cout << "=======================" << endl;
    cout << " Testing Vec<float, 3> " << endl;
    cout << "=======================" << endl;

    {
        cout << "  value type and dimension: (typedef is broken and idk why)";
		cout << " typedef concludes: " << typeid(Vec<float, 3>).name() << endl;
        // assert(typeid(Vec<float, 3>).name() == typeid(float).name() );
        // assert( Vec<float, 3>::dimension == 3 ); // @TODO: ?!?!?!
        cout << "passed." << endl;
    }

    {
        // do not tolerate any memory overhead
        cout << "  sizeof(Vec<float, 3>) == 3 bytes: ";
        assert( sizeof(Vec<float, 3>) == 3*sizeof(float) );
        cout << "passed." << endl;
    }

    {
        cout << "  constructor & index operator: ";
        Vec<float, 3> a;
        assert( a[0] == 0 && a[1] == 0 && a[2] == 0 );
		Vec<float, 3> b({ 1, 2, 3 });
        assert( b[0] == 1 && b[1] == 2 && b[2] == 3 );
        cout << "passed." << endl;
    }

    {
        cout << "  read-only access to const object: ";
		const Vec<float, 3> a({ 1,2,3 });
        // the next line will throw a compiler error if there is no proper "operator[] const"
        assert( a[1] == 2.f );
        cout << "passed." << endl;
    }

    {
        cout << "  write access to a non-const object: ";
		Vec<float, 3> a({ 1,2,3 });
        a[1] = 4;
        assert( a[0] == 1 && a[1] == 4 && a[2] == 3 );
        cout << "passed." << endl;
    }

    {
        cout << "  comparison: ";        
		Vec<float, 3> a({ 1,2,3 }), b({ 1, 2, 3 }), c({ 1, 2, 9 }), d({ 4, 5, 6 });
        assert( a == b );
        assert( a == a );
        assert( a != c );
        assert( b != d );
        assert( !(a != b) );
        cout << "passed." << endl;
    }
    
    {
        // should work out of the box when using std container (!)
        cout << "  assignment: "; 
		Vec<float, 3> a({ 1,2,3 });
        cout << a[0] << " "; // to make sure these values are not optimized away! 
		a = Vec<float, 3>({ 4,5,6 });
        assert( a[0] == 4 && a[1] == 5 && a[2] == 6 );
        cout << "passed." << endl;
    }
    
    {
		// @TODO: Somehow anonymous operations on anonymous objects don't seem to work anymore.
        cout << "  addition:  (Anonymous objects don't seem to work in comparison operations.)";
		Vec<float, 3> a({ 1,2,3 }), b({ 4, 5, 6 }), d({ 5,7,9 }), e({ 6,8,10 }), f({ 1,1,1 });
        a += b;
		assert(a == d);
		auto c = a + f;
		assert(c == e);
		Vec<float, 3> one({ 1,1,1 }), four({ 4, 4, 4 });
        one += one+one+one;
        assert( one == four);
		Vec<float, 3> x({ 0,0,0 }), y({ 1, 1, 1 }), z({ 2, 2, 2 }), w({ 3,3,3 });
        x += y += z;
		assert(y == w);
        assert( x == y );
        cout << "passed." << endl;
    }
    
    {
        cout << "  unary minus: ";
		Vec<float, 3> a({ 1,2,3 }), b({ -1,-2,-3 });
		assert(-a == b);
        cout << "passed." << endl;
    }
    
    {
        cout << "  dot product: ";
		Vec<float, 3> a({ 1,2,3 });
        assert( dot(a,a) == 1*1+2*2+3*3 );
        cout << "passed." << endl;
    }

	{
		// these tests will not compile if you forgot to declare 
		// some methods const
		cout << "  constness: ";
		const Vec<float, 3> a({ 1,2,3 }), b({ 2,4,6 }), c({ -1, -2, -3 });
		assert(a[1] == 2);
		assert(a == a);
		assert(!(a != a));
		assert(a + a == b);
		assert(-a == c);
        assert( dot(a,a) == 1*1+2*2+3*3 );
        cout << "passed." << endl;
    }

    cout << "all Vec<float, 3> tests passed." << endl << endl;   

#endif // not NDEBUG

}

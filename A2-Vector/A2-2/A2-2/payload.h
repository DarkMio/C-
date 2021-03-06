#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <memory>
#include <algorithm>

class Payload {

public:
    // data
    float x, y, z;

    // constructors
    Payload(float xx=0, float yy=0, float zz=0) : x(xx), y(yy), z(zz) { count_++; }
    Payload(const Payload& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) { count_++; }
	Payload(Payload&& rhs) : Payload() { swap(*this, rhs); }
    // destructor
    ~Payload()  { count_--; }

	friend void swap(Payload& lhs, Payload& rhs) {
		std::swap(lhs.y, rhs.y);
		std::swap(lhs.x, rhs.x);
		std::swap(lhs.z, rhs.z);
	}
    // assignment - keeps count the same 
    Payload& operator=(const Payload& rhs) { x=rhs.x; y=rhs.y; z=rhs.z; return *this; }

	Payload& operator=(Payload&& rhs) {
		x = rhs.x; y = rhs.y; z = rhs.z; return *this;
	}

    // comparison
    bool operator==(const Payload& rhs) const { return x==rhs.x && y==rhs.y && z==rhs.z; }

    // tell count
    static size_t count() { 
		return count_; 
	}

private:
    static size_t count_;

};


#endif // PAYLOAD_H

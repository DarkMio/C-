#include "Vec3f.h"

my::Vec3f::Vec3f()
	:mArray{0, 0, 0}
{
}

my::Vec3f::Vec3f(float x, float y, float z)
	: mArray{x, y, z}
{
}

std::ostream& operator<<(std::ostream& lhs, my::Vec3f const& rhs) {
	lhs << rhs.toString();
	return lhs;
}

my::Vec3f operator-(my::Vec3f const& rhs) {
	return my::Vec3f(-rhs[0], -rhs[1], -rhs[2]);
}

float dot(my::Vec3f const & lhs, my::Vec3f const & rhs) {
	return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}

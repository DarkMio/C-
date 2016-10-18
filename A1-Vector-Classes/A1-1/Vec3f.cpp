#include "Vec3f.h"

my::Vec3f::Vec3f()
	:mArray{0, 0, 0}
{
}

my::Vec3f::Vec3f(float x, float y, float z)
	: mArray{x, y, z}
{
}

float my::Vec3f::dot(Vec3f const & other) const {
	return mArray[0] * other[0] + mArray[1] * other[1] + mArray[2] * other[2];
}

std::string my::Vec3f::toString() const {
	return "[" + std::to_string(mArray[0]) + "," + std::to_string(mArray[1]) + "," + std::to_string(mArray[2]) + "]";
}

std::ostream& operator<<(std::ostream& lhs, my::Vec3f const& rhs) {
	lhs << rhs.toString();
	return lhs;
}

bool operator==(my::Vec3f const& lhs, my::Vec3f const& rhs) {
	return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2];
}

bool operator!=(my::Vec3f const& lhs, my::Vec3f const& rhs) {
	return !(lhs == rhs);
}

my::Vec3f operator-(my::Vec3f const& rhs) {
	return my::Vec3f(-rhs[0], -rhs[1], -rhs[2]);
}

my::Vec3f operator+(my::Vec3f const& lhs, my::Vec3f const& rhs) {
	my::Vec3f temp(lhs);
	temp += rhs;
	return temp;
}


my::Vec3f& operator+=(my::Vec3f& lhs, my::Vec3f const& rhs) {
	lhs[0] += rhs[0];
	lhs[1] += rhs[1];
	lhs[2] += rhs[2];
	return lhs;
}

float dot(my::Vec3f const & lhs, my::Vec3f const & rhs) {
	return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}

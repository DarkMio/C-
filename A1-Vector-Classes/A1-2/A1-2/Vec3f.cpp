/*

#include "Vec<float, 3>.h"

my::Vec<float, 3>::Vec<float, 3>()
	:mArray{0, 0, 0}
{
}

my::Vec<float, 3>::Vec<float, 3>(float x, float y, float z)
	: mArray{x, y, z}
{
}

float my::Vec<float, 3>::dot(Vec<float, 3> const & other) const {
	return mArray[0] * other[0] + mArray[1] * other[1] + mArray[2] * other[2];
}

std::string my::Vec<float, 3>::toString() const {
	return "[" + std::to_string(mArray[0]) + "," + std::to_string(mArray[1]) + "," + std::to_string(mArray[2]) + "]";
}

std::ostream& operator<<(std::ostream& lhs, my::Vec<float, 3> const& rhs) {
	lhs << rhs.toString();
	return lhs;
}

bool operator==(my::Vec<float, 3> const& lhs, my::Vec<float, 3> const& rhs) {
	return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2];
}

bool operator!=(my::Vec<float, 3> const& lhs, my::Vec<float, 3> const& rhs) {
	return !(lhs == rhs);
}

my::Vec<float, 3> operator-(my::Vec<float, 3> const& rhs) {
	return my::Vec<float, 3>(-rhs[0], -rhs[1], -rhs[2]);
}

my::Vec<float, 3> operator+(my::Vec<float, 3> const& lhs, my::Vec<float, 3> const& rhs) {
	my::Vec<float, 3> temp(lhs);
	temp += rhs;
	return temp;
}


my::Vec<float, 3>& operator+=(my::Vec<float, 3>& lhs, my::Vec<float, 3> const& rhs) {
	lhs[0] += rhs[0];
	lhs[1] += rhs[1];
	lhs[2] += rhs[2];
	return lhs;
}

float dot(my::Vec<float, 3> const & lhs, my::Vec<float, 3> const & rhs) {
	return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}
*/
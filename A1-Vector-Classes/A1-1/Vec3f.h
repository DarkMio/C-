#pragma once
#include <stdlib.h>
#include <array>
#include <string>

namespace my {
	class Vec3f {
		public:
		Vec3f();
		Vec3f(float x, float y, float z);
		int dimension() const { return 3; }
		typedef float value_type;
		float operator[](int const& i) const { return mArray[i]; }
		float& operator[](int const& i) { return mArray[i]; }
		float dot(Vec3f const& other) const;
		std::string toString() const;
		private:
		std::array<float, 3> mArray;
	};
}

std::ostream& operator<<(std::ostream&, my::Vec3f const&);
bool operator!=(my::Vec3f const&, my::Vec3f const&);
bool operator==(my::Vec3f const&, my::Vec3f const&);
my::Vec3f operator-(my::Vec3f const&);
my::Vec3f operator+(my::Vec3f const&, my::Vec3f const&);
my::Vec3f& operator+=(my::Vec3f& lhs, my::Vec3f const& rhs);
float dot(my::Vec3f const& lhs, my::Vec3f const& rhs);
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
		bool operator==(Vec3f const& other) const { return mArray == other.mArray; }
		Vec3f& operator+=(Vec3f const& rhs) { 
			mArray[0] += rhs[0];
			mArray[1] += rhs[1];
			mArray[2] += rhs[2];
			return *this;
		}
		Vec3f operator+(Vec3f const& rhs) {
			Vec3f temp(*this);
			temp += rhs;
			return temp;
		}
		std::string toString() const {
			return "[" + std::to_string(mArray[0]) + "," + mArray[1] + "," + mArray[2] + "]";
		}
		private:
		std::array<float, 3> mArray;
	};
}


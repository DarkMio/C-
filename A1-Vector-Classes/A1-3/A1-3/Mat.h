#pragma once
#include "Vec.h"
#include <array>

namespace my {
	template<typename T, int N>
	class Mat {
		private:
		std::array<Vec<T, N>, N> mArray;
		public:
		Mat(std::array<Vec<T, N>, N> const& v) : mArray(v) {}
		Mat(Mat<T, N> const& v) : mArray(v.mArray) {};
		Mat() : mArray() {}
		typedef T value_type;
		int size() const& { return (int)(sizeof(T) * N * N); }
		Mat<T, N> const identity() const {
			static const Mat<T, N> m = [] {
				std::array<Vec<T, N>, N> matArray;
				for (int i = 0; i < N; i++) {
					std::array<T, N> vecArray = {};
					vecArray[i] = 1;
					matArray[i] = Vec<T, N>(vecArray);
				}
				return Mat<T, N>(matArray);
			}();
			return m;
		}
		Vec<T, N> operator[] (int const& i) const {
			return mArray[i];
		}
		Vec<T, N> operator[] (int const& i) {
			return mArray[i];
		}
	};
}

template<typename T, int N>
bool operator==(my::Mat<T, N> const& lhs, my::Mat<T, N> const& rhs) {
	for (int i = 0; i < N; i++) {
		if (lhs[i] != rhs[i]) {
			return false;
		}
	}
	return true;
}

template<typename T, int N>
bool operator!=(my::Mat<T, N> const& lhs, my::Mat<T, N> const& rhs) {
	return !(lhs == rhs);
}

template<typename T, int N>
my::Vec<T, N> operator*(my::Mat<T, N> lhs, my::Vec<T, N> rhs) {
	std::array<T, N> values = {};
	for (int i = 0; i < N; i++) {
		T x = 0;
		for (int j = 0; j < N; j++) {
			x += lhs[j][i] * rhs[j];
		}
		values[i] = x;
	}
	return my::Vec<T, N>(values);
}

template<typename T, int N>
my::Mat<T, N> operator*(my::Mat<T, N> const& lhs, my::Mat<T, N> const& rhs) {
	auto row = [&lhs](int const& row) {
		std::array<T, N> rowie;
		for (int i = 0; i < N; i++) {
			rowie[i] = lhs[i][row];
		}
		return rowie;
	};
	std::array<my::Vec<T, N>, N> vecArray;

	for (int i = 0; i < N; i++) {
		auto rowie = row(i);
		for (int j = 0; j < N; j++) {
			auto column = rhs[j];
			T sum = 0;
			for (int k = 0; k < N; k++) {
				sum += column[k] * rowie[k];
			}
			vecArray[j][i] = sum;
		}
	}
	return my::Mat<T, N>(vecArray);
}
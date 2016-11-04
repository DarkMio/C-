#pragma once
#include <array>

namespace my {
	/**
		You hereby agree to be no common retard, but a smart retard.
		Smart retards use mathematical vectors with numerical types - not ypur classes.
		This trmplated class expects reasonable numerical types - otherwise it breaks.
		If it breaks, you're probably a commom retard.
	*/
	template<typename T, int N>
	class Vec {
		private:
		std::array<T, N> data_;
		public:
		Vec(std::array<T, N> const& v) : data_(v) {}
		Vec() : data_() {}
		typedef T value_type;
		int size() const {
			return (int)( N * sizeof(T));
		}
		std::array<T, N> getData() {
			return data_;
		}
		T operator[](int const& i) const {
			return data_[i];
		}
		T& operator[](int const& i) {
			return data_[i];
		}
		T dot(Vec<T, N> const& other) {
			T x = 0; // shesh, overflows could easily happen
			for (int i = 0; i < N; i++) {
				x += data_[i] * other[i];
			}
			return x;
		}
	};
};

template<typename T, int N, int M>
bool operator==(my::Vec<T, N> const& lhs, my::Vec<T, M> const& rhs) {
	static_assert(N == M, "Vector Sizes are different!");
	for (int i = 0; i < N; i++) {
		if (lhs[i] != rhs[i]) {
			return false;
		}
	}
	return true;
}

template<typename T, int N, int M>
bool operator!=(my::Vec<T, N> const& lhs, my::Vec<T, M> const& rhs) {
	return !(lhs == rhs);
}

template<typename T, int N>
my::Vec<T, N> operator-(my::Vec<T, N> const& rhs) {
	std::array<T, N> array;
	for (int i = 0; i < N; i++) {
		array[i] = -rhs[i];
	}
	return my::Vec<T, N>(array);
}

template<typename T, int N>
my::Vec<T, N> operator+(my::Vec<T, N> const& rhs, my::Vec<T, N> const& lhs) {
	std::array<T, N> array;
	for (int i = 0; i < N; i++) {
		array[i] = rhs[i] + lhs[i];
	}
	return my::Vec<T, N>(array);
}

template<typename T, int N>
my::Vec<T, N> operator-(my::Vec<T, N> const& rhs, my::Vec<T, N> const& lhs) {
	return rhs + (-lhs); // WHAT NOW, INFIDELS?
}

template<typename T, int N>
my::Vec<T, N>& operator+=(my::Vec<T, N>& lhs, my::Vec<T, N> const& rhs) {
	for (int i = 0; i < N; i++) {
		lhs[i] += rhs[i];
	}
	return lhs;
}

template<typename T, int N>
T& dot(my::Vec<T, N> const& rhs, my::Vec<T, N> const& lhs) {
	T x = 0; // shesh, overflows could easily happen
	for (int i = 0; i < N; i++) {
		x += rhs[i] * lhs[i];
	}
	return x;
}
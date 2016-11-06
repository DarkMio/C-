#pragma once
#include "Mat.h"
#include <string>
#include <sstream>
#include <iomanip>


namespace my {
	template<typename T, int N>
	inline std::string to_string(my::Mat<T, N> other, int width, int decimals) {
		// Good luck.
		std::stringstream ss;
		auto write_out = [&ss, &width, &decimals](T x) {
			ss << std::setw(width) << std::setprecision(decimals) << std::fixed << x;
		};

		std::string decimalText = decimals ? std::to_string(decimals) : "no";
		ss << ("Matrix, width=" + std::to_string(width) + ", " + decimalText + " decimals\n");
		ss << ("[");
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				write_out(other[i][j]);
			}
			if (i + 1 < N) {
				ss << ("\n");
				ss << (" ");
			}
		}
		ss << (" ]");
		return ss.str();
	}

	template<typename T, int N>
	inline std::string to_string(my::Mat<T, N> other) {
		return to_string(other, 6, 2);
	}

	template<typename T, int N>
	inline std::ostream& operator<<(std::ostream& lhs, my::Mat<T, N> const& rhs) {
		lhs << to_string(rhs);
		return lhs;
	}

	template<typename T, int N>
	inline std::string to_string(my::Vec<T, N> other, int width, int decimals) {
		std::stringstream ss;
		ss << "Vec" << N << " [";
		for (int i = 0; i < N; i++) {
			ss << std::setw(width) << std::setprecision(decimals) << std::fixed << other[i];
			if (i + 1 == N) {
				break;
			}
			ss << ", ";
		}
		ss << "]";
		return ss.str();
	}

	template<typename T, int N>
	inline std::string to_string(my::Vec<T, N> other) {
		return to_string(other, 6, 2);
	}

	template<typename T, int N>
	inline std::ostream& operator<<(std::ostream& lhs, my::Vec<T, N> const& rhs) {
		lhs << to_string(rhs);
		return lhs;
	}
}
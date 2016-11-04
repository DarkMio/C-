#pragma once
#include "Mat.h"
#include <string>

template<typename T, int N>
std::string to_string(my::Mat<T, N> other) {
	std::string text = "";
	for (int i = 0; i < N; i++) {
		text += to_string(other[i]);
		if (i + 1 == N) {
			break;
		}
		text += "\n";
	}
	return text;
}

template<typename T, int N>
inline std::ostream& operator<<(std::ostream& lhs, my::Vec<T, N> const& rhs) {
	lhs << to_string(rhs);
	return lhs;
}

template<typename T, int N>
inline std::string to_string(my::Vec<T, N> other) {
	std::string text = "[";
	for (int i = 0; i < N; i++) {
		text += std::to_string(other[i]);
		if (i + 1 == N) {
			break;
		}
		text += ", ";
	}
	text += "]";
	return text;
}

template<typename T, int N>
inline std::ostream& operator<<(std::ostream& lhs, my::Vec<T, N> const& rhs) {
	lhs << to_string(rhs);
	return lhs;
}
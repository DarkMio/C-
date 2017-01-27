#pragma once


template<typename T>
T clamp(T const& val, T const& min, T const& max) {
	if (val < min) {
		return min;
	} else if (val > max) {
		return max;
	}
	return val;
}

template<typename T>
T min(T const& val, T const& min) {
	if(val < min) {
		return min;
	}
	return val;
}

template<typename T>
T max(T const& val, T const& max) {
	if(val > max) {
		return max;
	}
	return val;
}
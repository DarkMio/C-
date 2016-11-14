#pragma once
#include <stdexcept>
#include <sstream>

namespace my {
	template<typename T>
	class vector {
		private:
		size_t space;
		size_t elements;
		T* mArray;
		public:
		vector(vector<T> const &) = delete;
		vector<T>& operator=(vector<T> const &) = delete;
		vector() : space(0), elements(0) {
			mArray = nullptr;
		}
		vector(size_t const& initialSize, T const& x = T()) : space(initialSize), elements(0) {
			if (initialSize == 0) {
				mArray = nullptr;
				return;
			}
			mArray = new T[initialSize];
			mArray[elements++] = x;
		}
		~vector() {
			delete[] mArray;
		}
		bool const empty() const {
			return elements == 0;
		}
		size_t size() const {
			return space;
		}
		void clear() {
			delete[] mArray;
			space = 1;
			elements = 0;
			mArray = new mArray[space];
		}
		void push_back(T const& value) {
			if (space <= elements) {
				// the good old swapperoo
				space ++;
				T* temp = new T[space];
				for (int i = 0; i < elements; i++) {
					temp[i] = mArray[i];
				}
				delete[] mArray;
				mArray = temp;
			}
			mArray[elements++] = value;
		}
		T pop_back() {
			T val = mArray[--elements];
			--space;
			T* temp = new T[space];
			for (int i = 0; i < elements; i++) {
				temp[i] = mArray[i];
			}
			delete[] mArray;
			mArray = temp;
			return val;
		}
		T operator[] (size_t const& element) const {
			return mArray[element];
		}
		T& operator[](size_t const& element) {
			return mArray[element];
		}
		T& at(size_t element) const {
			if (element >= elements) {
				std::stringstream ss;
				ss << "Only " << elements << " elements, you tried to access the" << (element+1) << "th";
				throw std::out_of_range(ss.str());
			}
			return mArray[element];
		}
	};
}
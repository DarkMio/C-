#pragma once
#include <stdexcept>
#include <sstream>

namespace my {
	template<typename T>
	class vector {
		private:
			size_t m_capacity;
			size_t m_size;
			T* mArray;
			void check_element(int const& element) const;
		public:
			vector(vector<T> const& rhs);
			vector<T>& operator=(vector<T> rhs) {
				swap(*this, rhs);
				return *this;
			}
			vector(vector<T>&& rhs);
			vector(size_t const& initialSize, T const& x);
			vector(size_t const& initialSize);
			vector();
			~vector();
			bool empty() const { return m_size == 0; }
			size_t size() const { return m_size; }
			size_t capacity() const { return m_capacity; }
			void reserve(size_t new_capacity);
			void clear();
			void push_back(T const& value);
			T pop_back();
			T operator[] (size_t const& element) const {
				return mArray[element];
			}
			T& operator[](size_t const& element) {
				return mArray[element];
			}
			T at(int const& element) const;
			T& at(int const& element);
			void shrink_to_fit();
			template<typename T>
			friend void swap(vector<T>& lhs, vector<T>& rhs) {
				std::swap(lhs.mArray, rhs.mArray);
				std::swap(lhs.m_capacity, rhs.m_capacity);
				std::swap(lhs.m_size, rhs.m_size);
			}
	};	
	template<typename T>
	vector<T>::vector(vector<T> const& rhs) : m_size(rhs.m_size), m_capacity(rhs.m_capacity), mArray(rhs.mArray) {};
	template<typename T>
	vector<T>::vector(vector<T>&& rhs) : vector<T>() {
		swap(*this, rhs);
	}
	template<typename T>
	vector<T>::vector(size_t const& initialSize, T const& x) : m_size(0), m_capacity(initialSize) {
		if (initialSize == 0) {
			mArray = nullptr;
			return;
		}
		mArray = static_cast<T*>(malloc(sizeof(T) * initialSize));
		new(mArray + m_size++) T(x);
	}
	template<typename T>
	vector<T>::vector(size_t const& initialSize) : m_size(0), m_capacity(initialSize) {
		if (initialSize == 0) {
			mArray = nullptr;
			return;
		}
		mArray = static_cast<T*>(malloc(sizeof(T) * initialSize));
	}
	template<typename T>
	vector<T>::vector() : m_size(0), m_capacity(0) {
		mArray = nullptr;
	}
	template<typename T>
	vector<T>::~vector() {
		for (size_t i = 0; i < m_size; i++) {
			mArray[i].~T();
		}
		free(mArray);
	}
	template<typename T>
	void vector<T>::reserve(size_t new_capacity) {
		if (m_capacity >= new_capacity) {
			return;
		}
		T* temp = static_cast<T*>(malloc(sizeof(T) * new_capacity));
		for (size_t i = 0; i < m_size; i++) {
			temp[i] = std::move(mArray[i]);
		}
		if (mArray != nullptr) {
			free(mArray);
		}
		mArray = temp;
		m_capacity = new_capacity;
	}
	template<typename T>
	void vector<T>::clear() {
		for (size_t i = 0; i < m_size; i++) {
			mArray[i].~T();
		}
		m_size = 0;
	}
	template<typename T>
	void vector<T>::push_back(T const& value) {
		if (m_capacity <= m_size) {
			auto new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
			reserve(new_capacity);
		}
		new (mArray + m_size++) T(value);
	}
	template<typename T>
	T vector<T>::pop_back() {
		T val(mArray[--m_size]);
		mArray[m_size].~T();
		return val;
	}
	template<typename T>
	T vector<T>::at(int const& element) const {
		check_element(element);
		return mArray[element];
	}
	template<typename T>
	T& vector<T>::at(int const& element) {
		check_element(element);
		return mArray[element];
	}
	template<typename T>
	void vector<T>::check_element(int const& element) const {
		if (element >= (int) m_size || element < 0) {
			int n = element + 1; // increment once, since we're writing some text now.
			std::string ending;
			auto x = n % 100;
			if (x > 10 && x < 14) {
				// increment over the 11, 12, 13, since they end with th.
				x += 3;
			}
			switch (x % 10) {
				case 1: ending = "st"; break;
				case 2: ending = "nd"; break;
				case 3: ending = "rd"; break;
				default: ending = "th"; break;
			}
			std::stringstream ss;
			ss << "Only " << m_size << " elements, you tried to access the " << n << ending;
			throw std::out_of_range(ss.str());
		}
	}
	template<typename T>
	void vector<T>::shrink_to_fit() {
		m_capacity = 0;
		reserve(m_size);
	}
}
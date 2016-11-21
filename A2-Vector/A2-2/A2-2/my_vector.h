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
		public:
			vector(vector<T> const& rhs) : mArray(rhs.mArray) {};
			vector<T>& operator=(vector<T> rhs) {
				swap(*this, rhs);
				return *this;
			}
			vector(vector<T>&& rhs) : vector<T>() {
				swap(*this, rhs);
			}
			vector(size_t const& initialSize, T const& x) : m_size(0), m_capacity(initialSize) {
				if (initialSize == 0) {
					mArray = nullptr;
					return;
				}
				mArray = static_cast<T*>(malloc(sizeof(T) * initialSize));
				new(mArray + m_size++) T(x);
				auto n = T::count();
			}
			vector(size_t const& initialSize) : m_size(0), m_capacity(initialSize) {
				if (initialSize == 0) {
					mArray = nullptr;
					return;
				}
				mArray = static_cast<T*>(malloc(sizeof(T) * initialSize));
			}
			vector() : m_size(0), m_capacity(0) {
				mArray = nullptr;
			}
			~vector() {
				for (size_t i = 0; i < m_size; i++) {
					mArray[i].~T();
				}
				free(mArray);
			}
			bool const empty() const {
				return m_size == 0;
			}
			size_t size() const {
				return m_size;
			}
			size_t capacity() const {
				return m_capacity;
			}
			void reserve(size_t new_capacity) {
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
			void clear() {
				for (size_t i = 0; i < m_size; i++) {
					mArray[i].~T();
				}
				m_size = 0;
			}
			void push_back(T const& value) {
				if (m_capacity <= m_size) {
					auto new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
					reserve(new_capacity);
				}
				new (mArray + m_size++) T(value);
			}
			T pop_back() {
				T val(mArray[--m_size]);
				mArray[m_size].~T();
				return val;
			}
			T operator[] const (size_t const& element) const {
				return mArray[element];
			}
			T& operator[](size_t const& element) {
				return mArray[element];
			}
			T& at(size_t element) const {
				if (element >= m_size) {
					std::stringstream ss;
					ss << "Only " << m_size << " elements, you tried to access the " << (element+1) << "th";
					throw std::out_of_range(ss.str());
				}
				return mArray[element];
			}
			template<typename T>
			friend void swap(vector<T> const& lhs, vector<T> const& rhs) {
				std::swap(lhs.mArray, rhs.mArray);
				std::swap(lhs.m_capacity, rhs.m_capacity);
				std::swap(lhs.m_size, rhs.m_size);
			}
	};


}
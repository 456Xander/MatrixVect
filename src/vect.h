#pragma once
#include <array>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <ostream>

template <std::size_t size>
class Vect {
   private:
	std::array<float, size> data;

   public:
	constexpr std::size_t getSize() const { return size; }
	float &get(const int i) const { return data[i]; }
	float &operator[](const std::size_t i) { return data[i]; }
	const float &operator[](const std::size_t i) const { return data[i]; }
	/*
	Vect(const std::initializer_list<float> list) {
		if (size != list.size()) {
			throw std::invalid_argument("Wrong number of arguments for vector");
		}
		for (auto curr = list.begin(), dest = this->data.begin();
			 curr < list.end(); curr++, dest++) {
			*dest = *curr;
		}
	}
	*/
	template <std::size_t N>
	Vect(const float (&arr)[N]) {
		static_assert(N == size, "Wrong Number of arguments for vector");
		std::cout << "N: " << N << "; size: " << size << std::endl;
		for (auto curr = arr, dest = this->data.begin(); curr < arr + N;
			 curr++, dest++) {
			*dest = *curr;
		}
	}

	Vect() { data.fill(.0f); }

	friend std::ostream &operator<<(std::ostream &stream, const Vect<size> v) {
		stream << '[';
		for (std::size_t i = 0; i < v.getSize(); i++) {
			stream << v[i];
			if (i != v.getSize() - 1) stream << ',';
		}
		stream << ']';
		return stream;
	}

	friend Vect<size> operator*(const int &i, const Vect<size> v) {
		Vect<size> n;
		for (std::size_t j = 0; j < v.getSize(); j++) {
			n[j] = i * v[j];
		}
		return n;
	}

	Vect<size> operator+(const Vect<size> &v) const {
		Vect<size> n;
		for (std::size_t i = 0; i < this->getSize(); i++) {
			n.data[i] = v.data[i] + this->data[i];
		}
		return n;
	}

	Vect<size> operator-(const Vect<size> &v) const {
		Vect<size> n;
		for (std::size_t i = 0; i < this->getSize(); i++) {
			n[i] = (*this)[i] - v[i];
		}
		return n;
	}

	Vect<size> operator-() const {
		Vect<size> n;
		for (std::size_t i = 0; i < this->getSize(); i++) {
			n[i] = (*this)[i] * -1;
		}
		return n;
	}

	Vect<size> operator*(const float f) const {
		Vect<size> n;
		for (std::size_t i = 0; i < this->getSize(); i++) {
			n[i] = (*this)[i] * f;
		}
		return n;
	}
	Vect<size> operator/(const float f) const {
		Vect<size> n;
		for (std::size_t i = 0; i < this->getSize(); i++) {
			n[i] = (*this)[i] / f;
		}
		return n;
	}

	Vect<size> &operator+=(Vect<size> &other) {
		for (std::size_t i = 0; i < other.getSize(); i++) {
			(*this)[i] += other[i];
		}
		return *this;
	}

	float dotProd(const Vect<size> &other) const {
		return std::inner_product(this->data.begin(), this->data.end(),
								  other.data.begin(), 0.0);
	}
	Vect<size> invert() const {
		Vect<size> n;
		for (std::size_t i = 0; i < size; i++) {
			n[i] = data[size - i - 1];
		}
		return n;
	}
};

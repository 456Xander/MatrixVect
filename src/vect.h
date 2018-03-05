#pragma once
#include <array>
#include <cstdlib>
#include <numeric>
#include <ostream>

template <std::size_t size>
class Vect {
   private:
	std::array<float, size> data;
	void checkLen(const Vect<size> &other) const {
		if (this->getSize() != other.getSize())
			throw std::invalid_argument("Vectors differ in lenght");
	}

   public:
	std::size_t getSize() const { return size; }
	float &get(const int i) const { return data[i]; }
	float &operator[](const std::size_t i) { return data[i]; }
	const float &operator[](const std::size_t i) const { return data[i]; }

	Vect(const std::initializer_list<float> list) {
		if (size != list.size()) {
			throw std::invalid_argument("Wrong number of arguments for vector");
		}
		for (auto curr = list.begin(), dest = this->data.begin();
			 curr < list.end(); curr++, dest++) {
			*dest = *curr;
		}
	}

	Vect() {}

	friend std::ostream &operator<<(std::ostream &stream, const Vect<size> v) {
		stream << '[';
		for (std::size_t i = 0; i < v.getSize(); i++) {
			stream << v[i];
			if (i != v.getSize() - 1) stream << ",";
		}
		stream << ']';
		return stream;
	}

	Vect<size> operator+(const Vect<size> &v) const {
		if (this->getSize() != v.getSize()) {
			throw std::invalid_argument(
				"Different sizes of vectors in addition");
		}
		Vect<size> n;
		for (std::size_t i = 0; i < this->getSize(); i++) {
			n.data[i] = v.data[i] + this->data[i];
		}
		return n;
	}

	Vect<size> operator-(const Vect<size> &v) const{
		if (this->getSize() != v.getSize()) {
			throw std::invalid_argument(
				"Different sizes of vectors in addition");
		}
		Vect<size> n;
		for (std::size_t i = 0; i < this->getSize(); i++) {
			n[i] = (*this)[i] - v[i];
		}
		return n;
	}

	Vect<size> operator-() const{
		Vect<size> n;
		for (std::size_t i = 0; i < this->getSize(); i++) {
			n[i] = (*this)[i] * -1;
		}
		return n;
	}

	Vect<size> operator*(const float f) const{
		Vect<size> n;
		for (std::size_t i = 0; i < this->getSize(); i++) {
			n[i] = (*this)[i] * f;
		}
		return n;
	}
	Vect<size> operator/(const float f) const{
		Vect<size> n;
		for (std::size_t i = 0; i < this->getSize(); i++) {
			n[i] = (*this)[i] / f;
		}
		return n;
	}
	float dotProd(const Vect<size> &other) const{
		this->checkLen(other);
		return std::inner_product(this->data.begin(), this->data.end(),
								  other.data.begin(), 0.0);
	}
	Vect<size> invert() const{
		Vect<size> n;
		for (std::size_t i = 0; i < size; i++) {
			n[i] = data[size - i - 1];
		}
		return n;
	}
};

#pragma once
#include <array>
#include <cstdlib>
#include <ostream>

template <std::size_t size>
class Vect {
   private:
	std::array<float, size> data;

   public:
	std::size_t getSize() { return size; }
	float &get(int i) { return data[i]; }
	float &operator[](std::size_t i) { return data[i]; }

	Vect(std::initializer_list<float> list) {
		if (size != list.size()) {
			throw std::invalid_argument("Wrong number of arguments for vector");
		}
		for (auto curr = list.begin(), dest = this->data.begin();
			 curr < list.end(); curr++, dest++) {
			*dest = *curr;
		}
	}

	Vect() {}

	friend std::ostream &operator<<(std::ostream &stream, Vect<size> v) {
		stream << '[';
		for (std::size_t i = 0; i < v.getSize(); i++) {
			stream << v[i];
			if (i != v.getSize() - 1) stream << ",";
		}
		stream << ']';
		return stream;
	}

	Vect<size> operator+(Vect<size> &v) {
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

	Vect<size> operator-(Vect<size> &v) {
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

	Vect<size> operator-() {
		Vect<size> n;
		for (std::size_t i = 0; i < this->getSize(); i++) {
			n[i] = (*this)[i] * -1;
		}
		return n;
	}

	Vect<size> operator*(float f) {
		Vect<size> n;
		for (std::size_t i = 0; i < this->getSize(); i++) {
			n[i] = (*this)[i] * f;
		}
		return n;
	}
	Vect<size> operator/(float f){
		Vect<size> n;
		for (std::size_t i = 0; i < this->getSize(); i++) {
			n[i] = (*this)[i] / f;
		}
		return n;
	}
};

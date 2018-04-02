#pragma once
#include <stdlib.h>
#include <array>
#include <iostream>
#include <tuple>

template <std::size_t rows, std::size_t cols>
class Matrix {
   private:
	std::array<std::array<float, cols>, rows> data;

   public:
	constexpr std::array<std::size_t, 2> getSize() const {
		return {rows, cols};
	}
	constexpr std::size_t getCols() const { return cols; }
	constexpr std::size_t getRows() const { return rows; }
	const std::array<float, cols> &operator[](int index) const {
		return data[index];
	}
	std::array<float, cols> &operator[](int index) { return data[index]; }

	Matrix() {
		for (auto &a : data) {
			a.fill(.0f);
		}
	}

	template <std::size_t R, std::size_t C>
	Matrix(const float (&arr)[R][C]) {
		static_assert(R == rows && C == cols,
					  "Wrong Number of arguments for Matrix");
		for (std::size_t i = 0; i < rows; i++) {
			for (std::size_t j = 0; j < cols; j++) {
				data[i][j] = arr[i][j];
			}
		}
	}

	friend std::ostream &operator<<(std::ostream &stream,
									const Matrix<rows, cols> m) {
		stream << '{';

		for (std::size_t i = 0; i < m.getRows(); i++) {
			stream << '[';
			for (std::size_t j = 0; j < m.getCols(); j++) {
				stream << m[i][j];
				if (j != m.getCols() - 1) stream << ',';
			}
			stream << ']';
			if (i != m.getRows() - 1) stream << std::endl;
		}
		stream << '}';
		return stream;
	}

	Matrix<rows, cols> operator+(Matrix<rows, cols> &o) {
		Matrix<rows, cols> n;
		for (std::size_t i = 0; i < rows; i++) {
			for (std::size_t j = 0; j < cols; j++) {
				n[i][j] = (*this)[i][j] + o[i][j];
			}
		}
		return n;
	}
	Matrix<rows, cols> operator-(Matrix<rows, cols> &o) {
		Matrix<rows, cols> n;
		for (std::size_t i = 0; i < rows; i++) {
			for (std::size_t j = 0; j < cols; j++) {
				n[i][j] = (*this)[i][j] - o[i][j];
			}
		}
		return n;
	}


};

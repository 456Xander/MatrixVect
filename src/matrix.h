#pragma once
#include <stdlib.h>
#include <array>
#include <iostream>
#include <tuple>

typedef float _matrix_type;

template <std::size_t rows, std::size_t cols>
class Matrix {
   private:
	std::array<std::array<_matrix_type, cols>, rows> data;

   public:
	constexpr std::array<std::size_t, 2> getSize() const {
		return {rows, cols};
	}
	constexpr std::size_t getCols() const { return cols; }
	constexpr std::size_t getRows() const { return rows; }
	const std::array<_matrix_type, cols> &operator[](int index) const {
		return data[index];
	}
	std::array<_matrix_type, cols> &operator[](int index) {
		return data[index];
	}

	Matrix() {
		for (auto &a : data) {
			a.fill(.0f);
		}
	}

	template <std::size_t R, std::size_t C>
	Matrix(const _matrix_type (&arr)[R][C]) {
		static_assert(R == rows && C == cols,
					  "Wrong Number of arguments for Matrix");
		for (std::size_t i = 0; i < rows; i++) {
			for (std::size_t j = 0; j < cols; j++) {
				data[i][j] = arr[i][j];
			}
		}
	}

	friend std::ostream &operator<<(std::ostream &stream,
									const Matrix<rows, cols> &m) {
		stream << '{';

		for (std::size_t i = 0; i < m.getRows(); i++) {
			if (i != 0) {
				stream << ' ';
			}
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

	template <std::size_t o_c>
	Matrix<rows, o_c> operator*(Matrix<cols, o_c> &o) {
		Matrix<rows, o_c> n;
		for (std::size_t i = 0; i < rows; i++) {
			for (std::size_t j = 0; j < o_c; j++) {
				_matrix_type val = 0;
				for (std::size_t k = 0; k < cols; k++) {
					val += (*this)[i][k] * o[k][j];
				}
				n[i][j] = val;
			}
		}
		return n;
	}

	std::tuple<Matrix<rows, cols>, Matrix<rows, cols>> lu_factors() {
		static_assert(rows == cols, "Can only LU-Factorize square Matrix");
		Matrix<rows, cols> l, u;
		for (std::size_t k = 0; k < rows; k++) {
			for (std::size_t m = k; m < rows; m++) {
				u[k][m] = data[k][m];
				for (std::size_t j = 0; j < k; j++) {
					u[k][m] -= l[k][j] * u[j][m];
				}
			}
			for (std::size_t i = 0; i < rows; i++) {
				l[i][k] = data[i][k];
				for (std::size_t j = 0; j < k; j++) {
					l[i][k] -= l[i][j] * u[j][k];
				}
				l[i][k] /= u[k][k];
			}
		}

		return std::make_tuple(l, u);
	}
};

class rtMatrix {
   private:
	const std::size_t rows, cols;
	_matrix_type *data;

   public:
	rtMatrix(const std::size_t rows, const std::size_t cols);
	const std::array<std::size_t, 2> getSize() const;
	std::size_t getRows() const { return rows; }
	std::size_t getCols() const { return cols; }
	const _matrix_type *operator[](const std::size_t index) const {
		return data + (index * cols);
	}
	_matrix_type *operator[](const std::size_t index) {
		return data + (index * cols);
	}
	friend std::ostream &operator<<(std::ostream &stream,
									const rtMatrix &m);
	rtMatrix operator+(const rtMatrix &o) const;
	rtMatrix operator-(const rtMatrix &o)const ;
	void operator+=(const rtMatrix &o);

};

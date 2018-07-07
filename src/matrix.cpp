#include "matrix.h"

rtMatrix::rtMatrix(const std::size_t rows, const std::size_t cols)
	: rows(rows), cols(cols) {
	data = new _matrix_type[rows * cols];
	std::fill(data, data + rows * cols, 0.0f);
}

rtMatrix::~rtMatrix() { delete[] data; }

rtMatrix::rtMatrix(const rtMatrix &o) noexcept : rows(o.rows), cols(o.cols) {
	data = new _matrix_type[rows * cols];
	std::copy(const_cast<const _matrix_type *>(o.data), o.dataEnd(), data);
}

const std::array<std::size_t, 2> rtMatrix::getSize() const {
	return std::array<std::size_t, 2>({this->rows, this->cols});
}

std::ostream &operator<<(std::ostream &stream, const rtMatrix &m) {
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

rtMatrix rtMatrix::operator+(const rtMatrix &o) const {
	rtMatrix ret(rows, cols);
	for (std::size_t i = 0; i < rows * cols; i++) {
		ret.data[i] = this->data[i] + o.data[i];
	}
	return ret;
}

rtMatrix rtMatrix::operator-(const rtMatrix &o) const {
	rtMatrix ret(rows, cols);
	for (std::size_t i = 0; i < rows * cols; i++) {
		ret.data[i] = this->data[i] - o.data[i];
	}
	return ret;
}
void rtMatrix::operator+=(const rtMatrix &o) {
	for (std::size_t i = 0; i < rows * cols; i++) {
		this->data[i] += o.data[i];
	}
}

std::tuple<rtMatrix *, rtMatrix *> rtMatrix::lu_factors() {
	if (rows != cols) {
		throw ERROR_NEED_SQUARE_MATRIX;
	}
	rtMatrix *l = new rtMatrix(rows, cols);
	rtMatrix *u = new rtMatrix(rows, cols);
	for (std::size_t k = 0; k < rows; k++) {
		for (std::size_t m = k; m < rows; m++) {
			(*u)[k][m] = (*this)[k][m];
			for (std::size_t j = 0; j < k; j++) {
				(*u)[k][m] -= (*l)[k][j] * (*u)[j][m];
			}
		}
		for(std::size_t i = 0; i < rows; i++){
			 (*l)[i][k] = (*this)[i][k];
			 for(std::size_t j = 0; j < k; j++){
				 (*l)[i][k] -= (*l)[i][j] * (*u)[j][k];
			 }
			 (*l)[i][k] /= (*u)[k][k];
		}
	}
	return std::make_tuple(l, u);
}

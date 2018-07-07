#include <iostream>
#include "matrix.h"
#include "vect.h"

int main() {
	Vect<2> v({1.0f, 1.5f});
	Vect<2> v4({1.0f, 1.5f});
	Vect<2> v2({1.0f, 1.5f});
	Vect<2> v3 = v2 + v;
	Vect<3> v3d({1.0f, 2.0f, 3.0f});
	std::cout << v << std::endl;
	std::cout << v2 << std::endl;
	std::cout << v3 << std::endl;
	std::cout << -v << std::endl;
	std::cout << v2.dotProd(v.invert()) << std::endl;

	Matrix<2, 2> m;
	Matrix<2, 2> m1({{1.0f, 2.0f}, {0.5f, 1.0f}});
	std::cout << m << std::endl;
	std::cout << m1 << std::endl;

	Matrix<3, 3> m2(
		{{1.0f, 2.0f, 4.0f}, {3.0f, 8.0f, 14.0f}, {2.0f, 6.0f, 13.0f}});
	std::tuple<Matrix<3, 3>, Matrix<3, 3>> lu = m2.lu_factors();
	std::cout << "===================================" << std::endl;
	std::cout << "         LU Decomposition          " << std::endl;
	std::cout << "===================================" << std::endl;
	std::cout << "==== L ====" << std::endl << std::get<0>(lu) << std::endl;
	std::cout << "==== H ====" << std::endl << std::get<1>(lu) << std::endl;

	rtMatrix rm(m2);
	auto lu2 = rm.lu_factors();
	std::cout << "==================================" << std::endl;
	std::cout << "     LU Decomposition rt size     " << std::endl;
	std::cout << "==================================" << std::endl;
	std::cout << "==== L ====" << std::endl << *std::get<0>(lu2) << std::endl;
	std::cout << "==== H ====" << std::endl << *std::get<1>(lu2) << std::endl;

	return 0;
}

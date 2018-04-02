#include <iostream>
#include "vect.h"
#include "matrix.h"
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

	Matrix<2,2> m;
	Matrix<2,2> m1({{1.0f,2.0f}, {0.5f, 1.0f}});
	std::cout << m << std::endl;
	std::cout << m1 << std::endl;
	return 0;
}

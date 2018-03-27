#include <iostream>
#include "vect.h"
int main() {
	Vect<2> v({1.0f, 1.5f});
	Vect<2> v4({1.0f, 1.5f, 2.0f});
	Vect<2> v2({1.0f, 1.5f, 2.0f});
	Vect<2> v3 = v2 + v;
	Vect<3> v3d({1.0f, 2.0f, 3.0f});
	std::cout << v << std::endl;
	std::cout << v2 << std::endl;
	std::cout << v3 << std::endl;
	std::cout << -v << std::endl;
	std::cout << v2.dotProd(v.invert()) << std::endl;
	return 0;
}

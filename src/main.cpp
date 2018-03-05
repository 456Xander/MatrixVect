#include <iostream>
#include "vect.h"
int main() {
	Vect<2> v{1.0, 1.5};
	Vect<2> v2{1.0, 1.5};
	Vect<2> v3 = v2 + v;
	std::cout << v << std::endl;
	std::cout << v2 << std::endl;
	std::cout << v3 << std::endl;
	std::cout << -v << std::endl;
	std::cout << v2.dotProd(v.invert()) << std::endl;
	return 0;
}

#include "implementazione_classe_rational.hpp"
#include <iostream>
#include <ostream>

int main() {
	rational<int> r1{9,6};
	rational<int> r2{10,21};
	rational<int> r3{5,-9};
	rational<int> r4{6,7};
	rational<int> r5{8,12};
	rational<int> r6{-13,7};
	rational<int> r7{1,1};
	rational<int> r8{-83,-52};
	rational<int> r_inf{3,0};
	rational<int> r_nan{0,0};
	rational<int> r_zero{0,726};
	
	std::cout << r1 << "\n";
	std::cout << r2 << "\n";
	std::cout << r3 << "\n";
	std::cout << r4 << "\n";
	std::cout << r5 << "\n";
	std::cout << r6 << "\n";
	std::cout << r7 << "\n";
	std::cout << r8 << "\n";
	std::cout << r_inf << "\n";
	std::cout << r_nan << "\n";
	std::cout << r_zero << "\n";
	
	// verifichiamo anche il funzionamento degli operatori
	std::cout << r1 << "+" << r3 << "=" << (r1 + r3) << "\n";
	std::cout << r4 << "+" << r5 << "=" << (r4 + r5) << "\n";
	std::cout << r7 << "-" << r2 << "=" << (r7 - r2) << "\n";
	std::cout << r_inf << "*" << r6 << "=" << (r_inf * r6) << "\n";
	std::cout << r_zero << "/" << r8 << "=" << (r_zero / r8) << "\n";
	std::cout << "r1 += r3 =" << (r1 += r3) << "\n";
	std::cout << "r1 -= r2 =" << (r1 -= r2) << "\n";
	std::cout << "r8 *= r7 =" << (r8 *= r7) << "\n";
	std::cout << "r_zero /= r_nan =" << (r_zero /= r_nan) << "\n";
	std::cout << "r2 /= r_inf =" << (r2 /= r_inf) << "\n";
	std::cout << "r5  /= r_zero =" << (r5 /= r_zero) << "\n";
	std::cout << "r_inf /= r_3 =" << (r_inf /= r3) << "\n";
	
	return 0;
}
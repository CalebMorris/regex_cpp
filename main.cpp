#include <iostream>

#include "regex.hpp"

int main () {
	Regex r("e{1,}");
	std::cout << r.match("e") << std::endl;
	std::cout << r.match("ete") << std::endl;
	return 0;
}
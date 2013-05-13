#include <iostream>

#include "regex.hpp"

int main () {
	Regex r("e{1,}");
	std::cout << r.match("e") << std::endl;
	return 0;
}
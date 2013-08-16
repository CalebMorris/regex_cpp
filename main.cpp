#include <iostream>

#include "regex.hpp"

int main () {
	Regex* reg = 0;
	free(reg); reg = new Regex("(\\(\\)");
	std::cout << reg->match("") << std::endl;
	return 0;
}
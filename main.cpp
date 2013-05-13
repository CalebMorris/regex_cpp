#include <iostream>

#include "regex.hpp"

int main () {
	//BUG: When multiple instances if Regex exist, there
	// are intermitent segfaults or wrong answers
	Regex r("e{1,}");
	Regex s("e{1}");
	Regex t("e{1,2}");
	std::cout << r.match("e") << std::endl;
	std::cout << r.match("ete") << std::endl;
	std::cout << s.match("e") << std::endl;
	std::cout << s.match("ete") << std::endl;
	std::cout << t.match("e") << std::endl;
	std::cout << t.match("ete") << std::endl;
	return 0;
}
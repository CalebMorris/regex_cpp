#include <iostream>

#include "regex.hpp"

int main () {
	Regex r("t?");
	/*
	std::cout << r.regex_to_postfix("t") << std::endl;
	std::cout << r.regex_to_postfix("te") << std::endl;
	std::cout << r.regex_to_postfix("t|e") << std::endl;
	std::cout << r.regex_to_postfix("tes|e") << std::endl;
	std::cout << r.regex_to_postfix("t|est") << std::endl;
	std::cout << r.regex_to_postfix("test|er") << std::endl;
	std::cout << r.regex_to_postfix("te|st|er") << std::endl;
	std::cout << r.regex_to_postfix("t*") << std::endl;
	std::cout << r.regex_to_postfix("t+e") << std::endl;
	std::cout << r.regex_to_postfix("t*es") << std::endl;
	std::cout << r.regex_to_postfix("te?s") << std::endl;
	std::cout << r.regex_to_postfix("(t)") << std::endl;
	std::cout << r.regex_to_postfix("(t*)") << std::endl;
	std::cout << r.regex_to_postfix("(t)*") << std::endl;
	std::cout << r.regex_to_postfix("(t*)*") << std::endl;
	std::cout << r.regex_to_postfix("(te)*") << std::endl;
	std::cout << r.regex_to_postfix("ab(te)st") << std::endl;
	std::cout << r.regex_to_postfix("(a|b)s") << std::endl;
	*/
	std::cout << r.toString() << std::endl;
	std::cout << r.match("t") << std::endl;
	return 0;
}

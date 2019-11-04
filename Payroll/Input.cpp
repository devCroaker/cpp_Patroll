#include "Input.h"

Input::Input() {}

Input::~Input() {}

std::string Input::getStr(std::string str) {
	bool valid = false;
	std::string input;

	if (str != "default") {
		std::cout << str << std::endl;
	}
	std::getline(std::cin, input);
	std::cout << std::endl;

	return input;
}

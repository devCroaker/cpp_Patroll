#include "Main.h"

template <typename T>
T get_input(std::string str, T b) {
	bool valid = false;
	T input;

	do {
		std::cout << str << std::endl;

		if (!(std::cin >> input)) {
			std::cout << "Invalid input" << std::endl;
		}
		else {
			valid = true;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	} while (!valid);
	std::cout << std::endl;

	return input;
}

template <>
std::string get_input(std::string str, std::string b) {
	bool valid = false;
	std::string input;

	do {
		std::cout << str << std::endl;

		if (!(std::getline(std::cin, input))) {
			std::cout << "Invalid input" << std::endl;
		}
		else {
			valid = true;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	} while (!valid);

	std::cout << std::endl;

	return input;
}
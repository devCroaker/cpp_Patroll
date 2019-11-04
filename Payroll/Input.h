#pragma once
#include <string>
#include <iostream>

class Input
{
public:
	Input();
	~Input();

	std::string getStr(std::string str);

	template <typename T>
	T get(std::string str, T b) {
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

};

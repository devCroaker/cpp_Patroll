#include "Phone.h"

Phone::Phone()
{
	for (int i = 0; i < 10; i++) {
		number[i] = 0;
	}
}

Phone::~Phone() {}

std::string Phone::get_number()
{
	std::stringstream ss;
	ss << "(" << number[0] << number[1] << number[2] << ") " << number[3] << number[4] << number[5] << "-" << number[6] << number[7] << number[8] << number[9];
	std::string num = ss.str();

	return num;
}

void Phone::parse_number(std::string num)
{
	int curr, j = 0;
	for (unsigned int i = 0; i < num.length(); i++) {
		curr = (int)num.at(i) - 48;
		if (curr > -1 && curr < 10) {
			number[j++] = curr;
		}
	}
}
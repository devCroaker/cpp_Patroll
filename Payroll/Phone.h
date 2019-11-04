#pragma once
#include <string>
#include <iomanip>
#include <sstream>  

class Phone
{
private:
	int number[10];
public:
	Phone();
	~Phone();

	std::string get_number();
	void parse_number(std::string);
};


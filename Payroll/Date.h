#pragma once
#include <string>
#include <iomanip>
#include <sstream>  

class Date
{
private:
	int day;
	int month;
	int year;
public:
	Date();
	~Date();
	void set_day(int);
	void set_month(int);
	void set_year(int);
	int get_day();
	int get_month();
	int get_year();

	std::string get_date();
	void parse_date(std::string);
};


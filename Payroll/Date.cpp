#include "Date.h"

Date::Date() 
{
	day = 1;
	month = 1;
	year = 1900;
}

Date::~Date() {}

void Date::set_day(int inDay)
{
	day = inDay;
}

void Date::set_month(int inMonth)
{
	month = inMonth;
}

void Date::set_year(int inYear)
{
	year = inYear;
}

int Date::get_day()
{
	return day;
}

int Date::get_month()
{
	return month;
}

int Date::get_year()
{
	return year;
}

std::string Date::get_date()
{
	std::stringstream ss;
	ss << std::right << std::setfill('0') << std::setw(2) << month << "/" << std::setw(2) << day << "/" << std::setw(4) << year;
	std::string date = ss.str();

	return date;
}

void Date::parse_date(std::string date)
{
	std::string num = "";
	int k = 0;
	for (unsigned int j = 0; j < date.length(); j++) {
		char cur = date.at(j);
		if (cur != '/') {
			num = num + cur;
		}
		else {
			if (k == 0) {
				month = std::stoi(num);
			}
			else if (k == 1) {
				day = std::stoi(num);
			}
			k++;
			num = "";
		}
	}
	year = std::stoi(num);
}
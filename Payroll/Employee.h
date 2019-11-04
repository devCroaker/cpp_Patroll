#pragma once
#include "Main.h"

int defaultDate[3] = { 1,1,1900 };

class Employee
{
friend class Payroll;
private:
	int emp_cd;
	std::string name;
	int *phone_number;
	std::string address;
	int join_date[3];
	std::string designation;
	char grade;
	double loan;
	double house_allowance;

public:
	Employee();
	Employee(int, std::string, int*, std::string = "unknown", int[3] = defaultDate, std::string = "New Hire", char = 'A', double = 0.00, double = 0.00);
	~Employee();
	void print_self();
	void save();
	void del_self();
	void get();
};


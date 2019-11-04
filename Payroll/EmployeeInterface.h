#pragma once
#include "Employee.h"
#include "Input.h"

class EmployeeInterface
{
private:
	std::string *employees;
	int numEmployees;
	int last_id;
	int is_emp(std::string);
	void addEmp();
	void print();
	void printEmpById(std::string);
	void deleteEmpById(std::string);
	void modifyEmpById(std::string);
	void salarySlipById(std::string);

public:
	EmployeeInterface();
	~EmployeeInterface();

	void run();
};

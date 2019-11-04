#pragma once
#include "Main.h"

class Payroll
{
private:
	int *empIds;
	Employee *employees;

public:
	Payroll();
	~Payroll();
	void init_menu();
	void add_emp();
	void upd_emp();
	void del_emp();
	void get_emp();
	void get_emps();
	void print_salary();
};


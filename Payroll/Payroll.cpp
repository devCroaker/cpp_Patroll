#include "Main.h"

Payroll::Payroll() {

	for (auto& p : fs::directory_iterator("Employees"))
		std::cout << p.path() << '\n';

	empIds = new int[];
	employees = new Employee[];
}

Payroll::~Payroll() {

}

void Payroll::init_menu() {

}

void Payroll::add_emp() {

}

void Payroll::upd_emp() {

}

void Payroll::del_emp() {

}

void Payroll::get_emp() {

}

void Payroll::get_emps() {

}

void Payroll::print_salary() {

}

#include "EmployeeInterface.h"

EmployeeInterface::EmployeeInterface()
{
	numEmployees = 0;
	employees = new std::string[numEmployees];

	for (auto& p : fs::directory_iterator("employees")) {
		numEmployees++;
		std::string* newArr = new std::string[numEmployees];
		std::copy(employees, employees + std::min((numEmployees -1), numEmployees), newArr);
		delete[] employees;
		employees = newArr;

		std::string empFile = p.path().string();
		int num = empFile.length() - 14;
		std::string empId = std::to_string(stoi(empFile.substr(10, num)));
		employees[numEmployees - 1] = empId;
		last_id = std::stoi(empId);
	}

}

EmployeeInterface::~EmployeeInterface()
{
	delete[] employees;
}

int EmployeeInterface::is_emp(std::string id)
{
	int isEmp = 0;
	for (int i = 0; i < numEmployees; i++) {
		if (id == employees[i]) {
			isEmp = 1;
			break;
		}
	}

	return isEmp;
}

void EmployeeInterface::run()
{
	Input input;
	std::cout << "Welcome to Employee DB++" << std::endl << std::endl;
	int option = 0;
	std::string id = "0";

	do {

		std::cout << "Choose an action" << std::endl;
		std::cout << "------------------------" << std::endl;
		std::cout << "1) Add an Employee" << std::endl;
		std::cout << "2) Modify an Employee" << std::endl;
		std::cout << "3) Delete an Employee" << std::endl;
		std::cout << "4) Print Employee Salary Slip" << std::endl;
		std::cout << "5) Print Employee by ID" << std::endl;
		std::cout << "6) Print Employee Table" << std::endl;
		std::cout << "7) Exit" << std::endl << std::endl;

		option = input.get("Please make a selection", option);

		switch (option) {
			case 1:
				addEmp();
				break;
			case 2:
				id = input.getStr("Please enter an Employee ID");
				modifyEmpById(id);
				break;
			case 3:
				id = input.getStr("Please enter an Employee ID");
				deleteEmpById(id);
				break;
			case 4:
				id = input.getStr("Please enter an Employee ID");
				salarySlipById(id);
				break;
			case 5:
				id = input.getStr("Please enter an Employee ID");
				printEmpById(id);
				break;
			case 6:
				print();
				break;
			case 7:
				break;
			default:
				std::cout << "Not a valid selection" << std::endl;
				break;
		}

	} while (option != 7);

}

void EmployeeInterface::addEmp() {

	Employee emp;
	Input input;

	std::cout << "Adding a new employee" << std::endl << "---------------------" << std::endl;
	emp.set_emp_cd(++last_id);
	emp.set_name(input.getStr("Please enter employees name:"));
	emp.set_address(input.getStr("Please enter employees address:"));
	emp.set_phone(input.getStr("Please enter your employees phone number as ten digits: (0123456789)"));
	emp.get_valid_date();
	emp.set_designation(input.getStr("Please enter employees designation:"));
	emp.get_valid_grade();
	emp.set_salary(input.get("Please enter employees Salary:", emp.get_salary()));
	emp.set_loan(input.get("Please enter employees loan amount:", emp.get_loan()));
	emp.set_allowance(input.get("Please enter employees allowance amount:", emp.get_allowance()));

	emp.write();

	numEmployees++;
	std::string* newArr = new std::string[numEmployees];
	std::copy(employees, employees + std::min((numEmployees - 1), numEmployees), newArr);
	delete[] employees;
	employees = newArr;
	employees[numEmployees-1] = std::to_string(last_id);

}

void EmployeeInterface::deleteEmpById(std::string id)
{
	int isEmp = is_emp(id);

	if (isEmp) {
		Employee emp;
		emp.get(id);
		if (emp.deleteSelf() != 0) {
			std::cout << "Failed to delete employee" << std::endl;
		}
		else {
			numEmployees--;
			std::string* newArr = new std::string[numEmployees];
			std::copy_if(employees, employees + std::max((numEmployees + 1), numEmployees), newArr, [id](std::string i) {return (i != id); });
			delete[] employees;
			employees = newArr;
		}
	}
	else {
		std::cout << id << " is not a valid employee ID" << std::endl;
	}
}

void EmployeeInterface::modifyEmpById(std::string id)
{
	int isEmp = is_emp(id);
	int cd = 0, param = -1;
	char modAgain = 'Y';

	if (isEmp) {
		Employee emp;
		Input input;

		emp.get(id);

		do {
			emp.printModify();
			do {
				param = input.get("Choose a field to modify (0-9):", param);
				if (param < 0 || param > 9) {
					std::cout << "Invalid index" << std::endl;
				}
			} while (param < 0 || param > 9);

			switch (param) {
			case 0:
				do {
					cd = input.get("Please enter an Employee code, not in use:", cd);
					isEmp = is_emp(std::to_string(cd));
					if (isEmp) {
						std::cout << "Code already in use" << std::endl;
					}
				} while (isEmp);
				deleteEmpById(std::to_string(emp.get_emp_cd()));
				emp.set_emp_cd(cd);
				break;
			case 1:
				emp.set_name(input.getStr("Please enter new name:"));
				break;
			case 2:
				emp.set_address(input.getStr("Please enter new address:"));
				break;
			case 3:
				emp.set_phone(input.getStr("Please enter your new phone number as ten digits: (0123456789)"));
				break;
			case 4:
				emp.get_valid_date();
				break;
			case 5:
				emp.set_designation(input.getStr("Please enter new designation:"));
				break;
			case 6:
				emp.get_valid_grade();
				break;
			case 7:
				emp.set_salary(input.get("Please enter employees Salary:", emp.get_salary()));
				break;
			case 8:
				emp.set_loan(input.get("Please enter employees loan amount:", emp.get_loan()));
				break;
			case 9:
				emp.set_allowance(input.get("Please enter employees allowance amount:", emp.get_allowance()));
				break;
			default:
				break;
			}

			emp.write();
			if (param == 0) {
				if (cd > last_id) {
					last_id = cd;
				}
				numEmployees++;
				std::string* newArr = new std::string[numEmployees];
				std::copy(employees, employees + std::min((numEmployees - 1), numEmployees), newArr);
				delete[] employees;
				employees = newArr;
				employees[numEmployees - 1] = std::to_string(cd);
			}

			modAgain = toupper(input.get("Do you wish to modify another field? 'Y'", modAgain));

		} while (modAgain == 'Y');
	}
	else {
		std::cout << id << " is not a valid employee ID" << std::endl;
	}
}

void EmployeeInterface::print()
{
	Employee emp;
	std::ios_base::fmtflags f(std::cout.flags());
	//name, number, join_dt, designation, grade, salery
	for (int i = 0; i < 115; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;

	std::cout << "|" << std::left << std::setw(9) << " ID" << "|";
	std::cout << std::setw(19) << " Name" << "|";
	std::cout << std::setw(16) << " Number" << "|";
	std::cout << std::setw(15) << " Hire Date" << "|";
	std::cout << std::setw(29) << " Designation" << "|";
	std::cout << std::setw(7) << " Grade" << "|";
	std::cout << std::setw(12) << " Salary" << "|" << std::endl;

	for (int i = 0; i < 115; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;

	for (int i = 0; i < numEmployees; i++) {
		std::string id = employees[i];
		emp.get(id);
		emp.printShortLine();
	}

	for (int i = 0; i < 115; i++) {
		std::cout << "-";
	}
	std::cout << std::endl << std::endl;

	std::cout.flags(f);
}

void EmployeeInterface::printEmpById(std::string id)
{
	int isEmp = is_emp(id);

	if (isEmp) {
		Employee emp;
		emp.get(id);
		emp.print();
	}
	else {
		std::cout << id << " is not a valid employee ID" << std::endl;
	}
}

void EmployeeInterface::salarySlipById(std::string id)
{
	Employee emp;
	int isEmp = is_emp(id);

	if (isEmp) {
		// I dont really know what I am supposed to calculate here

		emp.get(id);
		Input input;
		int month, days, hours, year;
		std::string strMonth, strHpd;
		do {
			month = input.get("Please enter the current month number:", 0);
			if (month > 13 && month < 0) {
				std::cout << "Invalid month" << std::endl;
			}
		} while (month > 13 && month < 0);

		do {
			year = input.get("Please enter the current full year:", 0);
			if (year < 1900) {
				std::cout << "Invalid year" << std::endl;
			}
		} while (year < 1900);

		do {
			days = input.get("Please enter number of days worked this month:", 0);
			if (days > 32 && days < 0) {
				std::cout << "Invalid number of days" << std::endl;
			}
		} while (days > 32 && days < 0);

		do {
			hours = input.get("Please enter number of hours worked this month:", 0);
			if (hours < 0) {
				std::cout << "Invalid number of hours" << std::endl;
			}
		} while (hours < 0);

		switch (month) {
			case 1:
				strMonth = "January";
				break;
			case 2:
				strMonth = "February";
				break;
			case 3:
				strMonth = "March";
				break;
			case 4:
				strMonth = "April";
				break;
			case 5:
				strMonth = "May";
				break;
			case 6:
				strMonth = "June";
				break;
			case 7:
				strMonth = "July";
				break;
			case 8:
				strMonth = "August";
				break;
			case 9:
				strMonth = "September";
				break;
			case 10:
				strMonth = "October";
				break;
			case 11:
				strMonth = "November";
				break;
			case 12:
				strMonth = "December";
				break;
			default:
				break;
		}
		std::stringstream ss;
		ss << "Worked " << hours << " hours over " << days << " Avg of " << std::fixed << std::setprecision(2) << (hours/days) << " per day";
		strHpd = ss.str();

		// Start the printing
		std::ios_base::fmtflags f(std::cout.flags());
		for (int i = 0; i < 60; i++) {
			std::cout << "-";
		}
		std::cout << std::endl;

		std::cout << "|" << std::left << std::setw(22) << " " << std::setw(36) << "Salary Slip" << "|" << std::endl;

		for (int i = 0; i < 60; i++) {
			std::cout << "-";
		}
		std::cout << std::endl;

		std::cout << "|" << std::setw(24) << " " << strMonth << ", " << std::setw(32 - strMonth.length()) << year << "|" << std::endl;
		std::cout << "| Employee: " << std::setw(24) << emp.get_name() << "Employee ID: " << std::setw(10) << emp.get_emp_cd() << "|" << std::endl;
		std::cout << "| Designation: " << std::setw(44) << emp.get_designation() << "|" << std::endl;
		std::cout << "| Employee Grade: " << std::setw(41) << emp.get_grade() << "|" << std::endl;
		std::cout << "| " << std::setw(57) << strHpd << "|" << std::endl << "|";

		for (int i = 0; i < 58; i++) {
			std::cout << "-";
		}
		std::cout << "|" << std::endl;

		std::cout << "| " << std::setw(40) << "Salary" << "| + " << std::right << std::fixed << std::setprecision(2) << std::setw(12) << (emp.get_salary()/12) << " |" << std::endl;
		std::cout << "| " << std::left << std::setw(40) << "Allowance" << "| + " << std::right << std::fixed << std::setprecision(2) << std::setw(12) << emp.get_allowance() << " |" << std::endl;
		std::cout << "| " << std::left << std::setw(40) << "Loan (5% interest)" << "| - " << std::right << std::fixed << std::setprecision(2) << std::setw(12) << (emp.get_loan()*0.05) << " |" << std::endl << "|";
		for (int i = 0; i < 58; i++) {
			std::cout << "-";
		}
		std::cout << "|" << std::endl;
		std::cout << "| " << std::setw(40) << "Net pay" << "| + " << std::right << std::fixed << std::setprecision(2) << std::setw(12) << ((emp.get_salary()/12) + emp.get_allowance() - (emp.get_loan()*0.05)) << " |" << std::endl;

		for (int i = 0; i < 60; i++) {
			std::cout << "-";
		}
		std::cout << std::endl << std::endl;

		std::cout.flags(f);
	}
	else {
		std::cout << id << " is not a valid employee ID" << std::endl;
	}
}
	
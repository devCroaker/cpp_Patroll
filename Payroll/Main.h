#pragma once
#include "Payroll.h"
#include "Employee.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <stdlib.h>
#include <ctype.h>

namespace fs = std::filesystem;

template <typename T>
T get_input(std::string str, T b);

template <>
std::string get_input(std::string str, std::string b);
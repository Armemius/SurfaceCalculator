#pragma once
#include "stdafx.h"

class Function {
public:
	double result(double x);
	void parse(std::string raw);
private:
	std::vector<IOperation*>* line;
};
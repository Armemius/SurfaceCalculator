#pragma once
#include "stdafx.h"

class Function {
public:
	Function();
	~Function();
	Function(std::string raw);
	double result(double x);
	void parse(std::string raw);
private:
	std::vector<IOperation*>* line = NULL;
};
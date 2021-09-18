#pragma once
#include "stdafx.h"

class Parser {
public:
	Parser();
	std::vector<IOperation*>* parse(std::string raw);
private:
	std::string raw = "\n";
	int pos = 0;
	std::stack<std::string> buff;
	std::vector<std::string> res;
	std::map<std::string, int> priors;

	bool isDigit(char ch);
	bool isLetter(char ch);
	bool isSign(char ch);
	int getPrior(std::string str);
	std::string parseNumber();
	std::string parseFunction();
};
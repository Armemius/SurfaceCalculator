#include "stdafx.h"

Parser::Parser() {
	this->priors.insert(std::pair<std::string, int>("+", 0));
	this->priors.insert(std::pair<std::string, int>("-", 0));
	this->priors.insert(std::pair<std::string, int>("*", 1));
	this->priors.insert(std::pair<std::string, int>("/", 1));
	this->priors.insert(std::pair<std::string, int>("^", 2));
	this->priors.insert(std::pair<std::string, int>("(", 10));
	this->priors.insert(std::pair<std::string, int>(")", 10));
}

std::vector<IOperation*>* Parser::parse(std::string raw) {
	for (int i = raw.size() - 1; i >= 0; --i) {
		if (raw[i] == '-') {
			if (i == 0) {
				raw.erase(i, 1);
				if (isDigit(raw[i])) {
					raw.insert(i, "inv(");
					i += 4;
					int j = 0;
					while (isDigit(raw[i + j]))
						++j;
					raw.insert(i + j, ")");
				}
				if (raw[i] == '(') {
					raw.insert(i, "inv");
					i += 3;
				}
				if (raw[i] == 'x') {
					raw.insert(i, "inv(");
					i += 5;
					raw.insert(i, ")");
				}
				if (isLetter(raw[i])) {
					raw.insert(i, "inv(");
					i += 4;
					int cnt = 0;
					for (int j = 0;;++j) {
						if (raw[i + j] == '(')
							cnt++;
						if (raw[i + j] == ')')
							cnt--;
						if (cnt == 0 && raw[i + j] == ')') {
							raw.insert(i + j, ")");
							break;
						}
					}
					int j = 0;
				}
				continue;
			}

			if (isSign(raw[i - 1]) && raw[i - 1] != ')') {
				if (isDigit(raw[i + 1])) {
					raw.erase(i, 1);
					raw.insert(i, "inv(");
					i += 4;
					int j = 0;
					while (isDigit(raw[i + j]))
						++j;
					raw.insert(i + j, ")");
				}
				if (raw[i + 1] == '(') {
					raw.erase(i, 1);
					raw.insert(i, "inv");
					i += 3;
				}
				if (raw[i + 1] == 'x') {
					raw.erase(i, 1);
					raw.insert(i, "inv(");
					i += 5;
					raw.insert(i, ")");
				}
				if (isLetter(raw[i + 1])) {
					raw.erase(i, 1);
					raw.insert(i, "inv(");
					i += 4;
					int cnt = 0;
					for (int j = 0;; ++j) {
						if (raw[i + j] == '(')
							cnt++;
						if (raw[i + j] == ')')
							cnt--;
						if (cnt == 0 && raw[i + j] == ')') {
							raw.insert(i + j, ")");
							break;
						}
					}
					int j = 0;
				}
			}
		}
	}
	raw = raw + "\n";
	this->raw = raw;
	std::cout << raw << "\n";
	this->pos = 0;
	while (raw[pos] != '\n') {
		char ch = raw[pos];
		if (isDigit(ch)) {
			res.push_back(this->parseNumber());
			continue;
		}

		if (isLetter(ch)) {
			std::string tmp = this->parseFunction();
			if (tmp == "x")
				res.push_back(tmp);
			else
				buff.push(tmp);
			continue;
		}

		if (isSign(ch)) {
			if (ch == '(') {
				buff.push("(");
				pos++;
				continue;
			}

			if (ch == ')') {
				for (;;) {
					if (buff.size() == 0)
						throw std::exception("Stack error: no '(' detected\n");
					if (this->buff.top() == "(") {
						buff.pop();
						break;
					}
					res.push_back(buff.top());
					buff.pop();
				}
				pos++;
				continue;
			}

			std::string symb(1, ch);
			int prior = getPrior(symb);
			if (buff.size() > 0) {
				while (getPrior(buff.top()) >= prior && buff.size() > 0 && getPrior(buff.top()) != 10) {
					res.push_back(buff.top());
					buff.pop();
					if (buff.size() == 0)
						break;
				}
			}
			buff.push(symb);
			pos++;
			continue;
		}
		std::cout << pos;
		throw std::exception("Parse error: undefined symbol in raw data\n");
	}
	while (buff.size() > 0) {
		std::string tmp = buff.top();
		if (tmp == "(")
			throw std::exception("Stack error: no ')' detected\n");
		res.push_back(tmp);
		buff.pop();
	}

	std::vector<IOperation*>* output = new std::vector<IOperation*>();
	for (std::string i : res) {
		if (isDigit(i[0])) {
			output->push_back(new Number(std::stod(i)));
			continue;
		}
		if (i.size() == 1 && i[0] == 'x') {
			output->push_back(new VarX());
			continue;
		}
		if (i.size() == 1 && i[0] == '+') {
			output->push_back(new Summ());
			continue;
		}
		if (i.size() == 1 && i[0] == '-') {
			output->push_back(new Minus());
			continue;
		}
		if (i.size() == 1 && i[0] == '*') {
			output->push_back(new Multiply());
			continue;
		}
		if (i.size() == 1 && i[0] == '/') {
			output->push_back(new Divide());
			continue;
		}
		if (i.size() == 1 && i[0] == '^') {
			output->push_back(new Pow());
			continue;
		}
		if (i == "ln") {
			output->push_back(new Ln());
			continue;
		}
		if (i == "sqrt") {
			output->push_back(new Sqrt());
			continue;
		}
		if (i == "exp") {
			output->push_back(new Exp());
			continue;
		}
		if (i == "sin") {
			output->push_back(new Sin());
			continue;
		}
		if (i == "cos") {
			output->push_back(new Cos());
			continue;
		}
		if (i == "inv") {
			output->push_back(new Inverse());
			continue;
		}
		throw std::exception("Parser error: Undefined formula");
	}
	return output;
}

bool Parser::isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

bool Parser::isLetter(char ch) {
	return ch >= 'a' && ch <= 'z';
}

bool Parser::isSign(char ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '^';
}

int Parser::getPrior(std::string oper) {
	if (isDigit(oper[0]))
		return -1;
	if (priors.find(oper) != priors.end())
		return priors[oper];
	return 3;
}

std::string Parser::parseNumber() {
	if (!isDigit(raw[pos]))
		throw std::exception("Parser error: no number detected while trying to call parseNumber() function\n");
	std::string number = "";
	while (raw[pos] != '\n' && (isDigit(raw[pos]))) {
		number += (raw[pos]);
		pos++;
	}
	return number;
}

std::string Parser::parseFunction() {
	if (!isLetter(raw[pos]))
		throw std::exception("Parser error: no letter detected while trying to call parseFunction() function\n");
	std::string func = "";
	while (raw[pos] != '\n' && isLetter(raw[pos])) {
		func += (raw[pos]);
		pos++;
	}
	return func;
}
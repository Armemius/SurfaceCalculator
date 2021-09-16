#include "stdafx.h"

double Function::result(double x) {
	std::stack<IOperation*> numbers;
	if (this == NULL)
		return 0;
	if (line == NULL)
		throw std::exception("Function error: line is null");
	for (IOperation* i : *line) {
		if (i->isNumber()) {
			numbers.push(i);
			continue;
		}
		if (i->requireSecond()) {
			IOperation* fst = numbers.top();
			numbers.pop();
			if (numbers.size() == 0)
				throw std::exception("Function error: no matching variable for binary function");
			IOperation* sec = numbers.top();
			numbers.pop();
			numbers.push(new Number(i->solve(sec->solve(x), fst->solve(x))));
		} else {
			IOperation* fst = numbers.top();
			numbers.pop();
			numbers.push(new Number(i->solve(fst->solve(x))));
		}
	}
	IOperation* elem = numbers.top();
	return elem->solve(x);
}

void Function::parse(std::string raw) {
	raw.erase(remove_if(raw.begin(), raw.end(), isspace), raw.end());
	Parser parser;
	this->line = parser.parse(raw);
	return;
}
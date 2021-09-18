#include "stdafx.h"

double GraphicHandler::getIntersection(Function* func1, Function* func2) {
	if (func1 == null || func2 == null) {
		return 0;
	}
	double EPS = 10;
	std::vector<double> range;
	for (double x = -50; x < 50; x += 0.1) {
		if (std::abs(func1->result(x) - func2->result(x)) < EPS) {
			if (range.size() < 2)
				range.push_back(x);
			else
				range.at(1) = x;
		}
	}
	while (EPS > 1e-6) {
		double start = range.at(0), finish = range.at(1);
		range = std::vector<double>();
		for (double x = start; x < finish; x += EPS / 100) {
			if (std::abs(func1->result(x) - func2->result(x)) < EPS) {
				if (range.size() < 2)
					range.push_back(x);
				else
					range.at(1) = x;
			}
		}
		EPS /= 10;
	}
	if (range.size() < 2)
		return INT_MAX;
	return (range.at(0) + range.at(1)) / 2.0;
}

double GraphicHandler::integral(Function* func, double from, double to) {
	double EPS = 1e-5;
	double step = 1, res = 0, prevRes = -999999.0;
	do {
		prevRes = res;
		res = 0;
		for (double str = from + step / 2; str < to - step / 2; str += step) {
			res += step * func->result(str);
		}
		step /= 5;
	} while (std::abs(res - prevRes) > EPS && step > 1e-6);
	
	return res;
}

void GraphicHandler::checkIntersects(Function* func1, Function* func2) {
	int intersects = 0;
	for (double x = -50; x < 50; x += 0.1) {
		if (std::abs(func1->result(x) - func2->result(x)) < 0.5) {
			intersects++;
			x++;
		}
	}
	if (intersects == 0)
		throw std::exception("Check error: less than 1 intersection\n");
	return;
}
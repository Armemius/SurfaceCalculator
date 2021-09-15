#include "stdafx.h"

double GraphicHandler::getIntersection(Function* func1, Function* func2) {
	if (func1 == null && func2 == null) {
		double EPS = 10;
		std::vector<double> range;
		for (double x = -50; x < 50; x += 0.1) {
			if (std::abs(FUNC_3 - FUNC_1) < EPS) {
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
				if (std::abs(FUNC_3 - FUNC_1) < EPS) {
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
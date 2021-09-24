#include "stdafx.h"

double GraphicHandler::getIntersection(Function* func1, Function* func2) {
	if (func1 == null || func2 == null) {
		return 0;
	}
	double EPS = 0.1;
	std::vector<double> range;
	for (double x = -50; x < 50; x += 0.001) {
		if (std::abs(func1->result(x) - func2->result(x)) < EPS) {
			range.push_back(x);
		}
	}
	double mid = (range.at(range.size() - 2) + range.at(range.size() - 1)) / 2.0;
	double devi = 666, res = 666;
	for (double x = mid - 0.3; x < mid + 0.3; x += 0.00001) {
		double tmp = std::abs(func1->result(x) - func2->result(x));
		if (tmp < devi) {
			res = x;
			devi = tmp;
		}
	}
	devi = 666; 
	double newRes = 666;
	for (uint64_t i = 1; i < 1e10; i *= 10) {
		devi = 666;
		newRes = 666;
		for (double x = res - 0.00005 / i; x < res + 0.00005 / i; x += 0.000001 / i) {
			double tmp = std::abs(func1->result(x) - func2->result(x));
			if (tmp < devi) {
				newRes = x;
				devi = tmp;
			}
		}
		res = newRes;
	}
	//std::cout << std::fixed << std::setprecision(8) << newRes << "\n";
	//std::cout << std::fixed << std::setprecision(20) << func1->result(newRes) - func2->result(newRes) << "\n";
	return newRes;
}

double GraphicHandler::integral(Function* func, double from, double to) {
	double EPS = 1e-5;
	double segments = 10, res = 0, prevRes = -999999.0;
	do {
		prevRes = res;
		res = 0;
		for (double str = from; str < to; str += std::abs(to - from) / segments) {
			res += (to - from) / segments * func->result(str + (to - from) / segments / 2);
		}
		segments++;
	} while (std::abs(res - prevRes) > EPS && segments < 1000);
	
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
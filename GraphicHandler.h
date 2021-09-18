#pragma once

class GraphicHandler {
public:
	static double getIntersection(Function* func1, Function* func2);
	static double integral(Function* func, double from, double to);
	static void checkIntersects(Function* func1, Function* func2);
};
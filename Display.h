#pragma once
#include "stdafx.h"

class Display {
public:
	void process();
	void setFunc1(Function* func);
	void setFunc2(Function* func);
	void setFunc3(Function* func);
private:
	// Screen size
	static const int horizontalPx = 1920;
	static const int verticalPx = 1080;

	Function* func1 = NULL;
	Function* func2 = NULL;
	Function* func3 = NULL;
};
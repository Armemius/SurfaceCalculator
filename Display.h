#pragma once
#include "stdafx.h"

class Display {
public:
	~Display();

	void setFunctions(Function* func1, Function* func2, Function* func3);
	void setFunc1(Function* func);
	void setFunc2(Function* func);
	void setFunc3(Function* func);

	void process();
	bool inProcess = true;
private:
	// Screen size
	static const int horizontalPx = 1920;
	static const int verticalPx = 1080;

	Function* func1 = NULL;
	Function* func2 = NULL;
	Function* func3 = NULL;

	double f1wf2;
	double f2wf3;
	double f1wf3;
};
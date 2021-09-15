#pragma once

class IOperation {
public:
	virtual double solve(double first, double second = 0) = 0;
	virtual bool requireSecond() = 0;
	virtual bool isNumber() = 0;
};

class Operation : public IOperation {
public:
	virtual double solve(double first, double second = 0) = 0;
	virtual bool requireSecond() = 0;
	virtual bool isNumber() override { 
		return false; 
	}
};

class Variable : public IOperation {
public:
	virtual double solve(double first, double second = 0) = 0;
	virtual bool requireSecond() = 0;
	virtual bool isNumber() override {
		return true;
	}
};
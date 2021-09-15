#pragma once
#include "stdafx.h"

class Number : public Variable {
public:
	Number(double);
	double solve(double first, double second) override;
	bool requireSecond() override;
	bool isNumber() override;
private:
	double num;
};

class VarX : public Variable {
	double solve(double first, double second) override;
	bool requireSecond() override;
};

class Summ : public Operation {
public:
	double solve(double first, double second) override;
	bool requireSecond() override;
};

class Minus : public Operation {
public:
	double solve(double first, double second) override;
	bool requireSecond() override;
};

class Multiply : public Operation {
public:
	double solve(double first, double second) override;
	bool requireSecond() override;
};

class Divide : public Operation {
public:
	double solve(double first, double second) override;
	bool requireSecond() override;
};

class Pow : public Operation {
public:
	double solve(double first, double second) override;
	bool requireSecond() override;
};

class Ln : public Operation {
public:
	double solve(double first, double second) override;
	bool requireSecond() override;
};

class Sqrt : public Operation {
public:
	double solve(double first, double second) override;
	bool requireSecond() override;
};

class Exp : public Operation {
public:
	double solve(double first, double second) override;
	bool requireSecond() override;
};

class Sin : public Operation {
public:
	double solve(double first, double second) override;
	bool requireSecond() override;
};

class Cos : public Operation {
public:
	double solve(double first, double second) override;
	bool requireSecond() override;
};

class Inverse : public Operation {
public:
	double solve(double first, double second) override;
	bool requireSecond() override;
};
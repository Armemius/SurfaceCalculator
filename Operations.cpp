#include "stdafx.h"

Number::Number(double num) {
	this->num = num;
}

double Number::solve(double first, double second) {
	return this->num;
}

bool Number::requireSecond() {
	return false;
}

bool Number::isNumber() {
	return true;
}

double VarX::solve(double first, double second) {
	return first;
}

bool VarX::requireSecond() {
	return false;
}

double Summ::solve(double first, double second) {
	return first + second;
}

bool Summ::requireSecond() {
	return true;
}

double Minus::solve(double first, double second) {
	return first - second;
}

bool Minus::requireSecond() {
	return true;
}

double Multiply::solve(double first, double second) {
	return first * second;
}

bool Multiply::requireSecond() {
	return true;
}

double Divide::solve(double first, double second) {
	return first / second;
}

bool Divide::requireSecond() {
	return true;
}

double Pow::solve(double first, double second) {
	return std::pow(first, second);
}

bool Pow::requireSecond() {
	return true;
}

double Ln::solve(double first, double second) {
	return std::log(first);
}

bool Ln::requireSecond() {
	return false;
}

double Sqrt::solve(double first, double second) {
	return std::sqrt(first);
}

bool Sqrt::requireSecond() {
	return false;
}

double Exp::solve(double first, double second) {
	return std::exp(first);
}

bool Exp::requireSecond() {
	return false;
}

double Sin::solve(double first, double second) {
	return std::sin(first);
}

bool Sin::requireSecond() {
	return false;
}

double Cos::solve(double first, double second) {
	return std::cos(first);
}

bool Cos::requireSecond() {
	return false;
}

double Inverse::solve(double first, double second) {
	return -first;
}

bool Inverse::requireSecond() {
	return false;
}
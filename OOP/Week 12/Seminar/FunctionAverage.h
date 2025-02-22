#pragma once
#include <iostream>
#include <utility>
#include <exception>
#include <fstream>

template <typename F1, typename F2>
class FunctionsAverage {
private:
	F1 first;
	F2 second;

public:
	FunctionsAverage(const F1& f, const F2& s);

	double average(int n) const;
};

template <typename F1, typename F2>
FunctionsAverage<F1, F2>::FunctionsAverage(const F1& f, const F2& s) : first(f), second(s) {}

template <typename F1, typename F2>
double FunctionsAverage<F1, F2>::average(int n) const {
	return (first(n) + second(n)) / 2.0;
}

#pragma once
#include<iostream>
#include<vector>

typedef std::vector<std::vector<double>> DoubleMatrix;

namespace Data {
	extern const double length;
	extern const double height;

	extern const int n;
	/*extern const int n2;*/
	extern const double step_space;
	extern const double step_space2;

	struct Parameters
	{
		double Dp = 8.85 * 1.e-7;
		double m = (2.5 * 1.e-6) / Dp;
		double nn = (1.67 * 1.e-4) / Dp;
		double c0 = 2;
	};


	void Transform(const int a1, const int b1, double& x, double& y);
	void Transform2(const double x, const double y, int& a, int& b);
	void Generating_a_node(int& a, int& b);
	double sgn(const double x);
	bool Particle_Inside_The_Area(const int a, const int b);
}
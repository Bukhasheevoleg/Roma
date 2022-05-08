#pragma once

#include <cmath> 
#include <math.h> 

#include"Data.h"

namespace Solver {

	extern const double number_of_particles;

	enum Direction {
		Right,
		Up,
		Left,
		Down,
	};

	class Equation
	{
	public:
		DoubleMatrix Solve();

	private:
		double Boundary_Condition(const int a1, const int b1);
		std::vector<double> Velocity(const int a1, const int b1);
		void walk(DoubleMatrix& A, int& a, int& b);
		Direction DirectionMovement(const double rand, const int a1, const int b1);
		double coff_S(const double x, const double y);
		double coff_C(const double x, const double y);
		double coff_D(const double x, const double y);
		double Pr_Jump(const int a1, const int b1);
		const Data::Parameters parameters;
	};

}

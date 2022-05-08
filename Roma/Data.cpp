#include"Data.h"

namespace Data {

	const double length = 3 * 1.e-3;
	const double height = 0.2;
	const int n = 20;
	/*const int n2 = height / step_space;*/
	const double step_space = length / n;
	const double step_space2 = height / n;


	void Transform(const int a1, const int b1, double& x, double& y)
	{
		x = step_space * b1;
		/*y = height - step_space * a1;*/
		y = height - step_space2 * a1;
	}

	void Transform2(const double x, const double y, int& a, int& b)
	{
		/*a = (height - y) / step_space;*/
		a = (height - y) / step_space2;
		b = x / step_space;
	}

	void Generating_a_node(int& a, int& b)
	{
		a = rand() % (n - 1) + 1;
		b = rand() % (n - 1) + 1;
	}

	double sgn(const double x)
	{
		if (x > 0)return 1;
		if (x == 0)return 0;
	}

	bool Particle_Inside_The_Area(const int a, const int b)
	{
		if (a > 0 && a < n && b > 0 && b < n)
			return true;
		else
			return false;
	}

}
#include "Solver.h"

namespace Solver {
	using namespace Data;

	const double number_of_particles = 1.E4;

	bool BelongsSegment(const double point, const double start_segment, const double end_segment)
	{
		if (point >= start_segment && point <= end_segment)
			return true;
		else
			return false;
	}

	std::vector<double> Equation::Velocity(const int a1, const int b1)
	{
		std::vector<double> vec(2);

		vec[0] = parameters.m;
		vec[1] = parameters.nn;

		double x, y;
		Data::Transform(a1, b1, x, y);
		if (vec[0] < (2 * coff_D(x, y)) / step_space && vec[1] < (2 * coff_D(x, y)) / step_space)
			return vec;
		else
			throw "Warning";
	}

	Direction Equation::DirectionMovement(const double rand, const int a1, const int b1)
	{
		Direction direction;
		double x, y;
		Data::Transform(a1, b1, x, y);
		std::vector<double> velocity = Velocity(a1, b1);
		double pr_right = (2 * coff_D(x, y) - step_space * velocity[0]) / (8 * coff_D(x, y));
		double pr_left = (2 * coff_D(x, y) + step_space * velocity[0]) / (8 * coff_D(x, y));
		double pr_up = (2 * coff_D(x, y) - step_space * velocity[1]) / (8 * coff_D(x, y));
		double pr_down = (2 * coff_D(x, y) + step_space * velocity[1]) / (8 * coff_D(x, y));

		if (BelongsSegment(rand, 0, pr_right))
			return direction = Right;
		if (BelongsSegment(rand, pr_right, pr_right + pr_left))
			return direction = Left;
		if (BelongsSegment(rand, pr_right + pr_left, pr_right + pr_left + pr_up))
			return direction = Up;
		if (BelongsSegment(rand, pr_right + pr_left + pr_up, 1))
			return direction = Down;
	}

	double Equation::Boundary_Condition(const int a1, const int b1)
	{
		return (a1 == n) ? 2 : 0;
	}

	double Equation::coff_S(const double x, const double y)
	{
		if (x == length)
			return -parameters.m;
		if (x == 0)
			return parameters.m;
		return 0;
	}

	double Equation::coff_C(const double x, const double y)
	{
		if (x == 0)
			return 1;
		if (x == length)
			return 1;
		if (y == height)
			return parameters.Dp;
		return 0;
	}

	double Equation::coff_D(const double x, const double y)
	{
		return 1;
	}

	double Equation::Pr_Jump(const int a1, const int b1)
	{
		double x, y;
		Transform(a1, b1, x, y);
		return coff_C(x, y) / (coff_C(x, y) + coff_S(x, y) * step_space);
	}

	void Equation::walk(DoubleMatrix& A, int& a, int& b) {

		while (Particle_Inside_The_Area(a, b)) {

			double direction_rand = (double)(rand()) / RAND_MAX;
			Direction direction = DirectionMovement(direction_rand, a, b);

			switch (direction) {

			case Down: {
				if (Particle_Inside_The_Area(a + 1, b))
				{
					A[a + 1][b] += 1;
					a++;
				}
				else {
					a++;
					break;
				}
			}
							 break;

			case Up: {
				if (Particle_Inside_The_Area(a - 1, b))
				{
					A[a - 1][b] += 1;
					a--;
				}
				else {
					a--;
					break;
				}
			}
						 break;

			case Right: {
				if (Particle_Inside_The_Area(a, b + 1))
				{
					A[a][b + 1] += 1;
					b++;
				}
				else {
					b++;
					break;
				}
			}
								break;

			case Left: {
				if (Particle_Inside_The_Area(a, b - 1))
				{
					A[a][b - 1] += 1;
					b--;
				}
				else {
					b--;
					break;
				}
			}
							 break;
			}

			//ѕроверка на отпрыгивание назад
			if (!Particle_Inside_The_Area(a, b) && a != n) {
				double pr = (double)(rand()) / RAND_MAX;
				if (pr <= Pr_Jump(a, b)) {
					switch (direction) {
					case Down: {
						a--;
						break;
					}
					case Up: {
						a++;
						break;
					}
					case Right: {
						b--;
						break;
					}
					case Left: {
						b++;
						break;
					}
					}
					A[a][b]++;
				}
			}
		}
	}

	DoubleMatrix Equation::Solve()
	{
		DoubleMatrix A(n + 1, std::vector<double>(n + 1));
		DoubleMatrix B(n + 1, std::vector<double>(n + 1));
		DoubleMatrix number_of_trajectories(n + 1, std::vector<double>(n + 1));

		int a, b;//строка и столбец узла
		double boundary;


		for (int k = 0; k < number_of_particles; k++) {

			//обнуление траектории
			A = DoubleMatrix(n + 1, std::vector<double>(n + 1));
			Generating_a_node(a, b);


			A[a][b] = A[a][b] + 1;

			walk(A, a, b);


			//ненулевые граничные услови€
			if (a == n || b == n || a == 0 || b == 0) {

				boundary = Boundary_Condition(a, b);

				for (int i = 0; i < n + 1; i++) {
					for (int j = 0; j < n + 1; j++) {
						B[i][j] += sgn(A[i][j]) * boundary;
					}
				}


				//учет траекторий посетивших узел
				for (int i = 0; i < n + 1; i++) {
					for (int j = 0; j < n + 1; j++) {
						number_of_trajectories[i][j] += sgn(A[i][j]);
					}
				}

			}
			if(k % 1000 == 0)std::cout << k << std::endl;
		}


		DoubleMatrix result(n + 1, std::vector<double>(n + 1));


		for (int i = 0; i < n + 1; i++) {
			for (int j = 0; j < n + 1; j++) {
				if (i == 0 || j == 0 || i == n || j == n) {
					result[i][j] = Boundary_Condition(i, j);
				}
				else {
					result[i][j] = B[i][j] / number_of_trajectories[i][j];
				}
			}
		}

		A.clear();
		B.clear();
		number_of_trajectories.clear();

		return result;
	}




}
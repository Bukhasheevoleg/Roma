#include"Solver.h"
#include"Graphics.h"

using namespace Solver;

int main()
{
	Equation equation;
	double start = clock();
	DoubleMatrix result = equation.Solve();
	double end = clock();
	double time = (end - start) / CLOCKS_PER_SEC;
	std::cout << "time:" << time << std::endl;

	NumericalSolution2D(result);
	NumericalSolution3D(result);
}
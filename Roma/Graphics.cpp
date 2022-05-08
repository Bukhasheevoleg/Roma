#include"Graphics.h"

void NumericalSolution3D(DoubleMatrix& iresult)
{
	using namespace std;
	ofstream out1;
	ofstream out2;

	out1.open("3D.txt");
	out2.open("3D.plt");

	double x,y;

	for (int i = 0; i < n + 1; i++) {
		for (int j = 0; j < n + 1; j++) {
			Transform(i, j, x, y);
			out1 << x << " ";
			out1 << y << " ";
			out1 << iresult[i][j] << endl;
		}
	}
	


	out2 << "set ticslevel 0" << endl;
	out2 << "set dgrid3d 300,300" << endl;

	out2 << "set pm3d at bs" << endl;
	out2 << "set hidden3d" << endl;
	out2 << "set xlabel 'X' " << endl;
	out2 << "set ylabel 'Z' " << endl;

	out2 << "splot 'C:/Users/1/source/repos/Roma/Roma/3D.txt' with lines title 'Numerical' " << endl;

	out1.close();
	out2.close();
	system("start 3D.plt");
}

void NumericalSolution2D(DoubleMatrix& iresult)
{
	using namespace std;
	ofstream out1;
	ofstream out2;
	ofstream out3;
	ofstream out4;

	out1.open("srez_x.txt");
	out2.open("srez_z.txt");
	out3.open("srez_x.plt");
	out4.open("srez_z.plt");

	double x = 0;
	int srez1 = n / 2;
	int srez2 = n / 2;
 	//—рез по x
	for (int j = 0; j < n + 1; j++)
	{
		out1 << x << " " << iresult[srez1][j] << endl; ;
		x = x + step_space;
	}

	//—рез по z
	double z = height;
	for (int i = 0; i < n + 1; i++)
	{
		out2 << z << " " << iresult[i][srez2] << endl; ;
		/*z -= step_space;*/
		z -= step_space2;
	}


	out3 << "set xrange[" << 0 - fabs(0.1 * length) << ":" << length + fabs(0.1 * length) << "]" << endl;
	out4 << "set xrange[" << 0 - fabs(0.1 * height) << ":" << height + fabs(0.1 * height) << "]" << endl;

	out3 << "set xlabel 'x' " << endl;
	out3 << "set ylabel 'Numerical solution' " << endl;
	out4 << "set xlabel 'z' " << endl;
	out4 << "set ylabel 'Numerical solution' " << endl;

	out3 << "plot 'C:/Users/1/source/repos/Roma/Roma/srez_x.txt' with lp lt rgb 'black' dashtype 7 lw 2 pt 7 ps 1 title 'Numerical'"<< endl;
	out4 << "plot 'C:/Users/1/source/repos/Roma/Roma/srez_z.txt' with lp lt rgb 'red' dashtype 7 lw 2 pt 7 ps 1 title 'Numerical'" << endl;


	out1.close();
	out2.close();
	out3.close();
	out4.close();
	system("start srez_x.plt");
	system("start srez_z.plt");

}



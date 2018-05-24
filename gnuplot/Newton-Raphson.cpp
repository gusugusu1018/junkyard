#include <iostream>
#include <cstdio>
#include <cmath>
#include <list>

using namespace std;
double newton(double x);
void gnuplot_2dFunctionGraph(FILE *gp);
void gnuplot_config(FILE *gp);
#define f(x) (x-1 - log(x+1))
#define df(x) (1 - 1.0/(x+1))

int main()
{
	FILE *gp;
	gp = popen("gnuplot","w");
	gnuplot_config(gp);
	fprintf(gp, "plot sin(x)\n");
	gnuplot_2dFunctionGraph(gp);
	double initial_value = -0.95;
	cout << newton(initial_value) << endl;
	return 0;
}

double newton(double val)
{
	double x1 = val - f(val) / df(val);

	if (fabs(x1-val) < 0.001) {
		return x1;
	} else {
		return newton(x1);
	}

}

void gnuplot_2dFunctionGraph(FILE *gp)
{

	fprintf(gp, "plot sin(x)\e");
}

void gnuplot_config(FILE *gp)
{

	double xrangemin = -10;
	double xrangemax = 10;
	double yrangemin = -10;
	double yrangemax = 10;
//	double zrangemin = 1000;
//	double zrangemax = 0;
	// save as gif
	//	fprintf(gp,"set terminal gif animate optimize size \n");
	//	fprintf(gp,"set output 'anime.gif'\n");

	fprintf(gp,"set xl \"x\"\n");	//set x axis name
	fprintf(gp,"set yl \"y\"\n");	//set y axis name
	fprintf(gp,"set zl \"z\"\n");	//set y axis name
	fprintf(gp,"set xrange [%f:%f]\n", xrangemin, xrangemax); //set range for x axis
	fprintf(gp,"set yrange [%f:%f]\n", yrangemin, yrangemax); //set range for y axis
//	fprintf(gp,"set zrange [%f:%f]\n", zrangemin, zrangemax); //set range for z axis
//	fprintf(gp,"unset tics\n");
	//    fprintf(gp,"set xtics 0.5\n");
	//    fprintf(gp,"set ytics 0.5\n");
	//    fprintf(gp,"set xlabel 'x' font 'Times, 20'\n");
	//    fprintf(gp,"set ylabel 'y' font 'Times, 20'\n");
	//    fprintf(gp,"set grid\n");
//	fprintf(gp,"set border 0\n");
	fprintf(gp,"set size square\n");
}


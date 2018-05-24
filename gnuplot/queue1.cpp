#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>

using namespace std;

double xrangemin = 0;
double xrangemax = 200;

double yrangemin = -2;
double yrangemax = 2;

void gnuplot_config(FILE *gp)
{

	// save as gif
	//	fprintf(gp,"set terminal gif animate optimize size \n");
	//	fprintf(gp,"set output 'anime.gif'\n");

	fprintf(gp,"set xl \"x\"\n");	//set x axis name
	fprintf(gp,"set yl \"y\"\n");	//set y axis name
	fprintf(gp,"set xrange [%f:%f]\n", xrangemin, xrangemax);
	fprintf(gp,"set yrange [%f:%f]\n", yrangemin, yrangemax);
	//	fprintf(gp,"unset tics\n");
	//    fprintf(gp,"set xtics 0.5\n");
	//    fprintf(gp,"set ytics 0.5\n");
	//    fprintf(gp,"set xlabel 'x' font 'Times, 20'\n");
	//    fprintf(gp,"set ylabel 'y' font 'Times, 20'\n");
	//    fprintf(gp,"set grid\n");
	//	fprintf(gp,"set border 0\n");
	//	fprintf(gp,"set size square\n");
}
int main (int argc, char const* argv[])
{
	queue<double> q1;
	double i, j, y;
	FILE *gp;
	gp = popen("gnuplot", "w");
	gnuplot_config(gp);
	for (j =0 ; j<5; j++)
	{
		fprintf(gp, "plot '-' w p pt 7 ps 0.5\n");
		for ( i = 0; i < 50; i++)
		{
			q1.push (i);
			cout << q1.back() << endl;
			y = sin(q1.back()*0.2);
			fprintf(gp, "%f %f\n", i , y);
			printf("%lf %lf\n",i , y);
		}
		fprintf(gp, "e\n");
		fprintf(gp, "plot '-' w p pt 7 ps 0.5\n");
		for (i = 50 ; i < 100; i++)
		{
			q1.push (i);
			cout << q1.front() << endl;
			y = sin(q1.front()*0.2);
			fprintf(gp, "%f %f\n", i , y);
			printf("%lf %lf\n",i , y);
			q1.pop();
		}
		fprintf(gp, "e\n");
	}
	fclose(gp);
	return 0;
}


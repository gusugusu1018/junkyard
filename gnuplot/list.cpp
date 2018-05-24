#include <iostream>
#include <cstdio>
#include <cmath>
#include <list>

using namespace std;

double xrangemin = -2;
double xrangemax = 2;
double yrangemin = -2;
double yrangemax = 2;
int listsize = 50;

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
	fprintf(gp,"set size square\n");
}
int main (int argc, char const* argv[])
{
	list<double> x,y;
	double i, j;
	FILE *gp;
	gp = popen("gnuplot", "w");
	gnuplot_config(gp);


	for ( i = 0; i < 1000; i++)
	{
		x.push_back (cos(i*0.2));
		y.push_back (sin(i*0.2));
		if (x.size() >= listsize){
			list<double>::iterator itx = x.begin();
			list<double>::iterator ity = y.begin();
			fprintf(gp, "plot '-' w p pt 7 ps 0.5\n");
			while (itx != x.end()){
				fprintf(gp, "%f %f\n", *itx , *ity);
				++itx;
				++ity;
			}
			fprintf(gp, "e\n");
			x.pop_front();
			y.pop_front();
		}
	}
	fclose(gp);
	return 0;
}


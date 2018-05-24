#include <stdio.h>
#include <cmath>

double xrangemin = -10;
double xrangemax = 10;

double yrangemin = -10;
double yrangemax = 10;

void gnuplot_config(FILE *gp);

int main(void)
{
	FILE *fp;
	FILE *gp;
	int ret;
	char s[256];
	int x,y;
	fp = fopen("x_data.dat","w");
	if (fp == NULL) {
		printf("cannot open!\n");
		return 1;
	}
	for (double i = 0.0; i < 10; i++)
	{
		fprintf(fp, "%lf %lf\n", i, cos(i));
	}
	fclose(fp);
	gp = popen("gnuplot -persist", "w");
//	gp = popen("gnuplot", "w");
	gnuplot_config(gp);  /* gnuplot configuration */
	fprintf(gp, "plot sin(x) w l title 'Sin(x)' lw 2\n");

	fprintf(gp, "replot 'x_data.dat' using 1:2 w l title 'Cos(x)' lw 2\n");
	fclose(gp);

	return 0;
}


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

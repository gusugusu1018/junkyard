#include <iostream>
#include <cstdio>
#include <cmath>
#include <list>

using namespace std;

void plot3dPosition(FILE *gp);
void gnuplot_config(FILE *gp);
float x,y,z;
float tx,ty,tz;
list<float> list_buf_3d_x, list_buf_3d_y, list_buf_3d_z;

int main()
{
	int t;
	FILE *gp;
	tx = 0;
	ty = 0;
	tz = 0;
	gp = popen("gnuplot","w");
	gnuplot_config(gp);
	for (t=0; t < 500;t++) {
		x = sin(t);
		y = cos(t);
		z = t;
		plot3dPosition(gp);
	}

	return 0;
}

void plot3dPosition(FILE *gp)	
{
	int listsize = 10;
			list_buf_3d_x.push_back(x);
			list_buf_3d_y.push_back(y);
			list_buf_3d_z.push_back(z);
			list<float>::iterator itx = list_buf_3d_x.begin();
			list<float>::iterator ity = list_buf_3d_y.begin();
			list<float>::iterator itz = list_buf_3d_z.begin();
			fprintf(gp, "splot '-' with points pointtype 7 pointsize 0.5 lc 3 title 'vPos'\n");
			fprintf(gp, "e\n");
			fprintf(gp, "replot '-' w p pt 7 ps 0.5 lc 1 title 'target'\n");
//			fprintf(gp, "splot '-' with line title 'vPos'\n");
			while (itx != list_buf_3d_x.end()){
				fprintf(gp, "%f %f %f\n", *itx , *ity, *itz);
				++itx;
				++ity;
				++itz;
			}
			fprintf(gp, "e\n");
			fprintf(gp, "%f %f %f\n", tx, ty, tz);
			fprintf(gp, "e\n");
			// buffer delete
			if (list_buf_3d_x.size() >= listsize){
				list_buf_3d_x.pop_front();
				list_buf_3d_y.pop_front();
				list_buf_3d_z.pop_front();
	}
}

void gnuplot_config(FILE *gp)
{

	double xrangemin = -3;
	double xrangemax = 3;
	double yrangemin = -3;
	double yrangemax = 3;
	double zrangemin = 1000;
	double zrangemax = 0;
	// save as gif
	//	fprintf(gp,"set terminal gif animate optimize size \n");
	//	fprintf(gp,"set output 'anime.gif'\n");

	fprintf(gp,"set xl \"x\"\n");	//set x axis name
	fprintf(gp,"set yl \"y\"\n");	//set y axis name
	fprintf(gp,"set zl \"z\"\n");	//set y axis name
	fprintf(gp,"set xrange [%f:%f]\n", xrangemin, xrangemax); //set range for x axis
	fprintf(gp,"set yrange [%f:%f]\n", yrangemin, yrangemax); //set range for y axis
	fprintf(gp,"set zrange [%f:%f]\n", zrangemin, zrangemax); //set range for z axis
//	fprintf(gp,"unset tics\n");
	//    fprintf(gp,"set xtics 0.5\n");
	//    fprintf(gp,"set ytics 0.5\n");
	//    fprintf(gp,"set xlabel 'x' font 'Times, 20'\n");
	//    fprintf(gp,"set ylabel 'y' font 'Times, 20'\n");
	//    fprintf(gp,"set grid\n");
//	fprintf(gp,"set border 0\n");
	fprintf(gp,"set size square\n");
}


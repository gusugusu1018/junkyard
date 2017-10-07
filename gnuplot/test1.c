#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(int argc, char **argv)
{
		FILE *gid;
		int i;
		double y;
		gid=popen("gnuplot","w");
		for (i=0; i<100 ;i++){
				y = i;
				fprintf(gid,"plot x*x*x+%f*x\n",y);
		}
		pclose(gid);
}

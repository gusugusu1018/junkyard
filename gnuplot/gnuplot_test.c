#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(int argc, char **argv)
{
		FILE *gid;
		int i;
		double x;
		gid=popen("gnuplot","w");
		for (i=0; i<100 ;i++){
				x = 0.03*i;
				fprintf(gid,"plot sin(x-%f*pi)\n",x);
		}
		pclose(gid);
}

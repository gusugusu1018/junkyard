#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float rand_uniform()
{
  float ret = ((float) rand() + 1.0f) / ((float) RAND_MAX + 2.0f);
  return ret;
}
float rand_normal(float mu, float sigma)
{
  float  z = sqrt(-2.0f * log(rand_uniform())) * sin(2.0f * M_PI * rand_uniform());
  return mu + sigma * z;
}

int main() {
	float mu=0.0f;
	float sigma=0.01f;
	float ret;
	FILE *fp;
	if ((fp=fopen("test.csv","w"))==NULL) {
		printf("Can't open file\n");
		return 1;
	}

	int i;
	for (i=0;i<1000;i++) {
		ret = rand_normal(mu,sigma);
		fprintf(fp,"%d\t%f\n",i,ret);
	}
	fclose(fp);
	return 0;
}

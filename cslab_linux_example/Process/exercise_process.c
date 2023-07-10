#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/time.h>
#include <limits.h>

int main(int agrc, char* argv[])
{

	int n = atoi(argv[1]);
	struct timeval t1, t2;


	gettimeofday(&t1,NULL);

	printf("current shell pid : %d\n", (int)getppid());
	
	int fibo[10000] = { 0 };

	int i = 0;
	fibo[0] = 1;
	fibo[1] = fibo[0];
	for(i = 0; i < n; i++)
	{
		fibo[i+2] = fibo[i] + fibo[i+1];
		printf("%d ",fibo[i]);
	}

	printf("\n");

	gettimeofday(&t2,NULL);

	printf("Process running time : %lf sec\n",(t2.tv_sec + t2.tv_usec*0.000001) - (t1.tv_sec + t1.tv_usec*0.000001));

	return 0;
}

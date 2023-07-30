#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>


int main(void)
{
	int i;
	struct timeval t1, t2;
	int *arr;

	gettimeofday(&t1, NULL);

	arr = (int*) malloc(sizeof(int) * 300000000);

	for(i = 0; i < 300000000; i++)
	{
		arr[i] = i;
	}
	
	free(arr);

	gettimeofday(&t2, NULL);

	printf("C_memory_allocation\n");
	printf("data type: int array\n");
	printf("data size: 300000000\n");
	printf("%f\n", (t2.tv_sec + t2.tv_usec*0.000001) - (t1.tv_sec + t1.tv_usec*0.000001) );

	return 0;

}

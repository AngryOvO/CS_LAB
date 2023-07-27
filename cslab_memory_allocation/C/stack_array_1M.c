#include <stdio.h>
#include <sys/times.h>
#include <unistd.h>
#include <sys/time.h>

int main(void)
{
	int i;
	struct timeval t1, t2;
	int arr[1000000];

	gettimeofday(&t1, NULL);

	for(i = 0; i < 1000000; i++);
	{
		arr[i] = i;
	}

	gettimeofday(&t2, NULL);

	printf("%f\n", (t2.tv_sec + t2.tv_usec*0.000001) - (t1.tv_sec + t1.tv_usec*0.000001) );

	return 0;

}

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int a;
	a = system("ps -ef | grep bash> result.txt");
	printf("Return Value : %d\n", a);

	return 0;
}


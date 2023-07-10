#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char *argv[3];
	
	printf("Before processing\n");

	argv[0] = "exercise_process.out";
	argv[1] = "10";
	argv[3] = NULL;

	if(execv("./exercise_process.out",argv) == -1)
	{
		perror("execv");
		exit(1);
	}
	
	printf("After processing\n");

	return 0;
}

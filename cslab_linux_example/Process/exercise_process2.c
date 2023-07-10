#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	char *argv[3];
	pid_t pid;
	int status;

	switch(pid = fork())
	{
		case 0:
			printf("Before processing\n");

			argv[0] = "exercise_process.out";
			argv[1] = "10";
			argv[2] = NULL;

			if(execv("exercise_process.out",argv) == -1)
			{
				perror("execv");
				exit(1);
			}
			break;
		default:
			wait(&status);
			printf("After processing\n");
			break;
	}

	return 0;
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int rfb, wfb;

	rfb = open(argv[1],O_RDONLY);

	if(rfb == -1)
	{
		char *error = "open ";
		strcpy(error,argv[1]);
		perror(error);
		exit(1);
	}
	
	wfb = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);

	if(wfb == -1)
	{
		char *error = "open ";
		strcpy(error,argv[2]);
		perror(error);
		exit(1);
	}
	int n;
	char buf[256];
	while((n = read(rfb,buf,6)) > 0)
		if(write(wfb,buf,n) != n) perror("Write");

	if(n == -1) perror("Read");

	close(rfb);
	close(wfb);

	return 0;
}



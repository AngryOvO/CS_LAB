#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	int fb;
	int n;
	char buf[256];

	fb = open("test.txt",O_RDWR);
	if(fb == -1)
	{
		perror("open");
		exit(1);
	}
	
	off_t start;

	start = lseek(fb, 26, SEEK_SET);
	n = read(fb, buf, 15);
	buf[n] = '\0';
	printf("%s\n",buf);
	return 0;
}

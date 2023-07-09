#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char* argv[])
{
	DIR *dp;
	struct dirent *dent;

	if((dp = opendir(argv[1])) == NULL)
	{
		perror(argv[1]);
		exit(1);
	}

	while((dent = readdir(dp)))
	{
		printf("%d %s\n",(int)dent->d_ino, dent->d_name);
	}

	closedir(dp);

	return 0;
}


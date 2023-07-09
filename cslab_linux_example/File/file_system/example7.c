#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	struct stat buf;

	stat("unix.txt",&buf);

	printf("Before Link Count = %d\n",(int)buf.st_nlink);

	symlink("unix.txt", "unix.sym");
	
	stat("unix.txt",&buf);

	printf("After Link Count = %d\n",(int)buf.st_nlink);

	return 0;
}

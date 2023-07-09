#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void)
{
	struct stat buf;

	chmod("unix.txt",S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);
	stat("unix.txt",&buf);
	printf("1.Mode = %o\n", (unsigned int)buf.st_mode);

	chmod("unix.txt",0770);
	stat("unix.txt",&buf);
	printf("2.Mode = %o\n", (unsigned int)buf.st_mode);

	return 0;
}

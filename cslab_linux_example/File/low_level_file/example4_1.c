#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int fd;
	// O_EXCL : 파일이 있는 경우엔 오류메시지 출력
	fd = open("unix.txt", O_CREAT | O_EXCL, 0644);
	if(fd == -1)
	{
		perror("Excl");
		exit(1);
	}
	close(fd);

	return 0;
}


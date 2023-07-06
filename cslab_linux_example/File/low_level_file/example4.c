#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int fd;
	mode_t mode;
	// S_IRUSR : 0400 : 소유자 read
	// S_IWUSR : 0200 : 소유자 write
	// S_IRGRP : 0040 : 그룹 read
	// S_IROTH : 0004 : 기타 사용자 read
	// 따라서 mode > 0644 의 권한을 갖게됨
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	fd = open("unix.txt", O_CREAT, mode);
	//O_CREAT 플래그 > 파일이 없을 시 생성 근데 mode의 권한으로
	if(fd == -1)
	{
		perror("Creat");
		exit(1);
	}
	close(fd);
	return 0;
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
 lseek : 파일 오프셋 지정
 offset 으로 지정한 크기만큼 이동
 */

int main(void)
{
	int fd, n;
	off_t start, cur;
	char buf[256];

	fd = open("unix.txt",O_RDONLY);
	if(fd == -1)
	{
		perror("Open unix.txt");
		exit(1);
	}
	//SEEK_CUR : 현재  위치 기준
	start = lseek(fd, 0, SEEK_CUR);
	n = read(fd, buf, 255);
	buf[n] = '\0';
	printf("Offset start = %d, Read Str = %s, n = %d\n", (int)start, buf,n);
	cur = lseek(fd,0,SEEK_CUR);
	printf("Offset cur = %d\n",(int)cur);
	// SEEK_SET : 시작 위치 기준 > 즉 아래 start는 시작위치 기준 5바이트만큼
	start = lseek(fd,5,SEEK_SET);
	n = read(fd, buf, 255);
	buf[n] = '\0';
	printf("Offset start = %d, Read Str = %s", (int)start, buf);

	close(fd);

	return 0;
}

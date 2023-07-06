#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/*
 파일 기술자 제어 : fcntl
 파일 기술자가 가리키는 파일에 cmd로 지정한 명령을 수행
 */
int main(void)
{
	int fd, flags;

	fd = open("unix.txt", O_RDWR);
	if(fd == -1)
	{
		perror("open");
		exit(1);
	}
	// F_GETFL : 플래그 상태 정보를 읽어옴
	// 플래그 상태정보를 읽기를 실패하는 경우 에러
	if((flags = fcntl(fd, F_GETFL)) == -1)
	{
		perror("fcntl");
		exit(1);
	}
	// O_APPEND : 파일에 맨 끝에 내용을 추가함
	// flags 값을 수정 : O_RDWR > O_APPEND 
	flags |= O_APPEND;
	//F_SETFL > flags값으로 플래그 상태를 세팅
	if(fcntl(fd, F_SETFL,flags) == -1)
	{
		perror("fcntl");
		exit(1);
	}

	if(write(fd,"Hanbit Media", 12)!= 12) perror("write");
	close(fd);

	return 0;
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/*
 *read - write example
 unix.txt의 값을 읽기 전용으로 읽어와서
 unix.bak에 그 내용을 씀
 */

int main(void)
{
	int rfd, wfd, n;
	char buf[10];

	rfd = open("unix.txt", O_RDONLY);
	if(rfd == -1)
	{
		perror("Open unix.txt");
		exit(1);
	}
	// O_TRUNC > 파일을 생성 & 쓰기 옵션으로 open시 내용 모두 지움
	wfd = open("unix.bak", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(wfd == -1)
	{
		perror("Open unix.bak");
		exit(1);
	}
	//실제로 읽어온 바이트 개수를 리턴
	while((n = read(rfd, buf, 6)) > 0)
		// 실제로 쓴 값이랑 읽어온 값이랑 맞지 않으면 에러 호출
		if(write(wfd, buf, n) != n) perror("Write");

	if(n == -1) perror("Read");

	close(rfd);
	close(wfd);

	return 0;

}


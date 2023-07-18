#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <string.h>
#define PORTNUM 6464

/* SOCKET TCP CLIENT
 *
 * 같은 포트 번호로 소켓 및 소켓 주소 구조체 생성
 * connect - 서버에 접속 요청
 * recv - 서버가 보낸 데이터 읽기
 * */

int main(void)
{
	int sd;
	char buf[256];
	struct sockaddr_in sin;

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("113.198.137.118");

	if(connect(sd, (struct sockaddr *)&sin, sizeof(sin)))
	{
		perror("connect");
		exit(1);
	}

	if(recv(sd, buf, sizeof(buf), 0) == -1)
	{
		perror("recv");
		exit(1);
	}

	close(sd);
	printf("From Server: %s\n", buf);
	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <inttypes.h>
#include <string.h>
/* SOCKET TCP SERVER
* 포트번호를 새로 부여하고
* socket - 소켓 생성
* bind - 이름 부여
* listen - 접속 요청 대기
* accept - 연결
* send - 전송
 * */
#define PORTNUM 6464

int main(void) 
{
	char buf[256];
	struct sockaddr_in sin, cli;
	int sd, ns, clientlen = sizeof(cli);

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) // 소켓 생성
	{
		perror("socket");
		exit(1);
	}
	int optvalue = 1;
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optvalue, sizeof(optvalue));

	memset((char *)&sin, '\0', sizeof(sin)); // 소켓 주소 구조체 생성
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("0.0.0.0");
	// 0.0.0.0인 경우 모든 IP로부터의 요청을 받을 수 있음

	if(bind(sd,(struct sockaddr *)&sin, sizeof(sin))) // 이름 부여
	{
		perror("bind");
		exit(1);
	}

	if(listen(sd,5)) // 접속 요청 대
	{
		perror("listen");
		exit(1);
	}

	if((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1)// 연결
	{
		perror("accept");
		exit(1);
	}
	sprintf(buf, "Your IP address is %s", inet_ntoa(cli.sin_addr)); // 전송
	if(send(ns,buf,strlen(buf) + 1, 0) == -1)
	{
		perror("send");
		exit(1);
	}

	close(ns);
	close(sd);

	return 0;
}

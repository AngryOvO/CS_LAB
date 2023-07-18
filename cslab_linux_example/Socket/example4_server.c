#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
/* 반복서버_SERVER
 *
 * 데몬 프로세스가 직접 모든 클라이언트의 요청을 차례로 처리
 * 즉 서버에서 하나의 프로세스가
 * 반복문을 통해서 클라이언트의 요청을 하나씩 반복해서 처리
 * 프로세스 목록을 보게되면 서버 프로세스 하나만 실행될 것임
 */
#define PORTNUM 6432

int main(void)
{
	char buf[256];
	struct sockaddr_in sin, cli;
	int sd, ns, clientlen = sizeof(cli);

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("0.0.0.0");

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}
	int optvalue = 1;
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optvalue, sizeof(optvalue));

	if(bind(sd, (struct sockaddr *)&sin, sizeof(sin)))
	{
		perror("bind");
		exit(1);
	}

	if(listen(sd,5))
	{
		perror("listen");
		exit(1);
	}

	while(1)
	{
		if((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1)
		{
			perror("accept");
			exit(1);
		}

		sprintf(buf, "%s", inet_ntoa(cli.sin_addr));

		strcpy(buf, "Welcome to Network Server!!!");
		if (send(ns, buf, strlen(buf) + 1 , 0) == -1)
		{
			perror("send");
			exit(1);
		}

		if(recv(ns, buf, sizeof(buf), 0) == -1)
		{
			perror("recv");
			exit(1);
		}
		printf("** From Client : %s\n",buf);
		close(ns);
	}
	close(sd);

	return 0;
}

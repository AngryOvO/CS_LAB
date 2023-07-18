#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORTNUM 6724
/* 동시동작_SERVER
 * 동시동작 서버는 클라이언트가 접속 했을 시 fork를 호출
 * 새 프로세스가 생성되면서 클라이언트에게 서버차원에서의 동작 수행
 * 프로세스 상태를 보게되면
 * 클라이언트가 접속했을 시 
 * 프로세스의 수가 증가했음을 확인하면 됨
 */
int main(void)
{
	char buf[256];
	struct sockaddr_in sin, cli;
	int sd, ns, clientlen = sizeof(cli);

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("0.0.0.0");

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

		switch(fork())
		{
			case 0:
				close(sd);
				strcpy(buf,"Welcome to Server");
				if(send(ns, buf, strlen(buf) + 1, 0) == -1)
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
				exit(0);
		}
		close(ns);
	}
	return 0;
}


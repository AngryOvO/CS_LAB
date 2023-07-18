#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <inttypes.h>
#include <string.h>
/* SOCKET UDP SERVER
 * 소켓 생성 (SOCK_DGRAM : 통신방식 UDP)
 * 소켓 종류 : AF_INET : 인터넷 소켓
 * 포트번호 : 6652
 * bind - 소켓 기술자와 소켓 주소 구조체 연결
 * recvfrom - 클라이언트의 메시지 수신 함수 
 * >> UDP 서버가 수신을 받을 때까지 계속 켜져 있어야 하므로
 * >> while무한루프를 통해서 가둬둠
 *
 * sendto - 클라이언트로 데이터 보내기
 * */
#define PORTNUM 6652

int main(void)
{
	char buf[256];
	struct sockaddr_in sin, cli;
	int sd, clientlen = sizeof(cli);

	if((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
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

	while(1)
	{
		if((recvfrom(sd, buf, 255, 0, (struct sockaddr *)&cli, &clientlen)) == -1)
		{
			perror("recvfrom");
			exit(1);
		}

		printf("** From Client : %s\n", buf);
		strcpy(buf, "Hello Client");
		if((sendto(sd, buf, strlen(buf) + 1, 0, (struct sockaddr *)&cli, sizeof(cli))) == -1)
		{
			perror("sendto");
			exit(1);
		}
	}

	return 0;

}

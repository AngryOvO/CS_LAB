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

int main(int argc, char* argv[]) 
{
	char buf[65536];
	struct sockaddr_in sin, cli;
	int sd, ns, clientlen = sizeof(cli);
	FILE *fp;
	size_t bytesRead;
	char filelink[1024];
	char filename[1024];

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) // 소켓 생성
	{
		perror("socket");
		exit(1);
	}
	int optvalue = 1;
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &optvalue, sizeof(optvalue));

	int portnum = atoi(argv[2]);

	memset((char *)&sin, '\0', sizeof(sin)); // 소켓 주소 구조체 생성
	sin.sin_family = AF_INET;
	sin.sin_port = htons(portnum);
	sin.sin_addr.s_addr = inet_addr("0.0.0.0");
	// 0.0.0.0인 경우 모든 IP로부터의 요청을 받을 수 있음

	if(bind(sd,(struct sockaddr *)&sin, sizeof(sin))) // 이름 부여
	{
		perror("bind");
		exit(1);
	}

	if(listen(sd,10)) // 접속 요청 대기
	{
		perror("listen");
		exit(1);
	}
	while(1)
	{

		if((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1)// 연결
		{
			perror("accept");
			exit(1);
		}

		bytesRead = recv(ns, buf, sizeof(buf) - 1, 0);
		if(bytesRead <= 0)
		{
			perror("recv");
			exit(1);
		}	
		

		buf[bytesRead] = '\0';
		printf("%s",buf);
	
		char* targetaddress = strtok(buf,"\n");
		char* ptr = strtok(targetaddress, "/");
		ptr = strtok(NULL, " ");
		
		strcpy(filename,ptr);
		printf("%s\n",filename);
	
		strcpy(filelink,argv[1]);
		strcat(filelink,"/");
		strcat(filelink,filename);

		printf("%s\n",filelink);

		if((fp = fopen(filelink,"rb")) == NULL)
		{
			sprintf(filelink,"%s/index.html", argv[1]);
			printf("\n\n%s\n\n",filelink);
			if((fp = fopen(filelink,"rb")) == NULL)
			{
				sprintf(buf,"%s","NOT FOUND");
				if(send(ns, buf, strlen(buf) + 1, 0) == -1)
				{
					perror("send");
					exit(1);
				}
				exit(1);
			}
		}
		int i;
		for(i = 0; i < 65536; i++)
		{
			buf[i] = '\0';
		}

		char http_response[1024];
		sprintf(http_response, "HTTP/1.1  200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: %ld\r\n\r\n", bytesRead);
		
		send(ns, http_response, strlen(http_response), 0);


		while((bytesRead = fread(buf, 1, sizeof(buf), fp)) > 0)
		{
			if(send(ns,buf,bytesRead,0) == -1)
			{
				perror("send");
				exit(1);
			}
		}
		
		printf("=====\n");
		printf("%s\n",buf);

		fclose(fp);
		close(ns);
	}
	close(sd);

	return 0;
}

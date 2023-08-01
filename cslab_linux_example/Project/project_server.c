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
	FILE * fp;
	FILE * fp2;
	size_t bytesRead;
	char filelink[1024];
	char filename[1024];
	int num1, num2, sum;
	char resultsum[255];


	
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
	fp2 = fopen("log.txt", "w");
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
	
		char* targetaddress = strtok(buf,"\n");
		char* ptr;
		ptr = strtok(targetaddress, "/");
		while((ptr = strchr(targetaddress,'/')) != NULL)
		{
			ptr = strtok(targetaddress, "/");
		}
		ptr = strtok(NULL, " ");
		
		strcpy(filename,ptr);
	
		strcpy(filelink,argv[1]);
		strcat(filelink,"/");
		strcat(filelink,filename);

		if((fp = fopen(filelink,"rb")) == NULL)
		{
			if(strstr(filelink,"total.cgi"))
			{
				char* ptr = strtok(filelink, "=");

				ptr = strtok(NULL,"&");

				char filenum1[256];
				char filenum2[256];

				strcpy(filenum1,ptr);

				ptr = strtok(NULL, "=");
			
				ptr = strtok(NULL, "\0");

				strcpy(filenum2,ptr);

				num1 = atoi(filenum1);
				num2 = atoi(filenum2);

				sum = 0;
			
				int i = 0;

				for(i = num1; i <= num2; i++)
					sum = sum + i;
			
				sprintf(resultsum,"%d\n",sum);
			
				fp = fopen("example/result.txt","w+");

				fputs(resultsum,fp);
			}
			else
			{
				sprintf(filelink,"%s/index.html", argv[1]);

				if((fp = fopen(filelink,"rb")) == NULL)
				{
					sprintf(filelink, "%s/notfound.html", argv[1]);
					fp = fopen(filelink,"rb");
				}
			}
		}

		fseek(fp, 0, SEEK_END);
		long int file_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		int i;
		for(i = 0; i < 65536; i++)
		{
			buf[i] = '\0';
		}

		char http_response[256];
		char* http_type;


		if(strstr(filelink, ".html"))
			http_type = "text/html";
		else if(strstr(filelink, ".gif"))
			http_type = "image/gif";
		else if(strstr(filelink, ".jpg") || strstr(filelink, ".jpeg"))
			http_type = "image/jpeg";
		else if(strstr(filelink, ".cgi") || strstr(filelink, ".txt"))
			http_type = "text/plain";
		else
			http_type = "application/octet-stream";

		sprintf(http_response, "HTTP/1.1  200 OK\r\nContent-Type: %s; charset=utf-8\r\nContent-Length: %ld\r\n\r\n",http_type , file_size);
		
		send(ns, http_response, strlen(http_response), 0);

		while((bytesRead = fread(buf, 1, sizeof(buf), fp)) > 0)
		{
			if(send(ns,buf,bytesRead,0) == -1)
			{
				perror("send");
				exit(1);
			}
		}
		
		char text_log[256];

		sprintf(text_log, "%s_%s_%ld\n", inet_ntoa(cli.sin_addr), filelink, file_size);
		fp2 = fopen("log.txt","a");
		fputs(text_log,fp2);
		

		fclose(fp2);
		fclose(fp);
		close(ns);
	}
	fclose(fp2);
	close(sd);

	return 0;
}

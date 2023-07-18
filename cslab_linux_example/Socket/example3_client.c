#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <inttypes.h>
#include <string.h>
/* SOCKET UDP CLIENT
 */
#define PORTNUM 6652

int main(void)
{
	int sd, n;
	char buf[256];
	struct sockaddr_in sin;

	if((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("113.198.137.118");

	strcpy(buf, "I am a client.");
	if(sendto(sd, buf, strlen(buf) + 1, 0, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		perror("sendto");
		exit(1);
	}

	n = recvfrom(sd, buf, 255, 0, NULL, NULL);
	buf[n] = '\0';
	printf("** From Server : %s\n", buf);

	return 0;
}

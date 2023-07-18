#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
/* 
 * SOCKET : IP 주소 변환하기
 * 문자열 형태로 IP 주소를 받아서
 * 이진 형태로 변환한 뒤 변환한 IP 주소를 통해서
 * 호스트 명을 검색하고
 * 그 호스트 명과 이진 주소였던 IP 주소를 
 * 다시 문자열로 변환해서 출력
 * */


int main(void)
{
	in_addr_t addr;
	struct hostent *hp;
	struct in_addr in;

	if((addr = inet_addr("142.250.206.206")) == (in_addr_t)-1)
	{
		printf("ERROR : inet_addr(142.250.206.206\n");
		exit(1);
	}

	hp = gethostbyaddr((char *)&addr, 4, AF_INET);

	if(hp == NULL)
	{
		(void)printf("Host information not found\n");
		exit(2);
	}

	printf("Name = %s\n", hp->h_name);

	(void)memcpy(&in.s_addr, *hp->h_addr_list, sizeof(in.s_addr));
	printf("IP = %s\n", inet_ntoa(in));

	return 0;
}


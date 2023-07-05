#include <stdio.h>

void main()
{
	char *temp= "Paras";

	int i;
	i = 0;

	temp[0] = 'F';

	for(i = 0; i < 5; i++)
		printf("%c\n",temp[i]);

}

// 10번 라인에서 segment fault 발생 : 리터럴 영역에서 readonly로 되어있는 문자 리터럴의 값을 변경하려해서 
// 에러가 발생함

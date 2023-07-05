#include <stdio.h>

void main()
{
	int i, num, j;
	j = 1;
	printf("Enter the number:");
	scanf("%d", &num);

	for(i=1; i<num; i++)
		j=j*i;

	printf("The factorial of %d is %d \n",num ,j);
}
// j가 0으로 초기화 되어있어 팩토리얼 값이 올바르지 않게 출력됨
// j를 1로 초기화해야 함


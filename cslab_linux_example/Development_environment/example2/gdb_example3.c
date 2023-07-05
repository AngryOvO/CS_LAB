#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	char *buf;

	buf = malloc(1<<31);
	strcpy(buf, "This is Test");
	printf("%s\n", buf);

	return 0;

}

// 9번 line 에서 2의 31승만큼의 비트를 할당하려고해서 시스템 차원에서 거부를 했기 때문에
// buf에 NULL값이 할당됨
// 그 상태에서 buf가 가리키는 곳에 문자열을 복사하려고 하니 잘못된 메모리 접근으로 인한
// segmantfault가 발생

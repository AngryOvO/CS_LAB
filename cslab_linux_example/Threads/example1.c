#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
/* thread
 * 스레드 생성 후 스레드 func에서 sleep실행
 * 그러므로 아래 main이 먼저 출력
 * 그 이후 pthread_join 함수가 실행
 * 그러므로 스레드 루틴으로 설정된 threadfunc가 끝나기 전까지
 * main은 실행을 대기중
 * 즉 스레드 루틴에서 Hello, world! 출력 후
 * main2 출력
 *
 * */


void *threadfunc(void *vargp);

/* thread routine */

void *threadfunc(void *vargp)
{
	sleep(1);
	printf("Hello, world!\n");
	return NULL;
}

int main()
{
	pthread_t tid;
	// 스레드 생성
	pthread_create(&tid, NULL, threadfunc, NULL);
	printf("main\n");

	pthread_join(tid, NULL);

	printf("main2\n");
	sleep(2);

	return 0;
}


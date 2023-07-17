#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
/* thread
 * 스레드 생성 후 스레드 func에서 sleep실행
 * 그러므로 아래 main이 먼저 출력
 * 그 이후 pthread_detach 함수 실행
 * 메인 함수와 스레드 루틴이 분리
 * 서로 다른 프로세스라고 생각하면 쉬운듯
 * 그래서 스레드 루틴에서 sleep함수를 콜 하는 사이에
 * main2 까지 출력 후 sleep함수를 콜
 * 메인에서 sleep함수를 콜 하는동안 스레드 루틴 종료 후 자원 회수
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
	pthread_create(&tid,NULL,threadfunc,NULL);
	printf("main\n");

	pthread_detach(tid);

	printf("main2\n");
	sleep(2);

	return 0;
}


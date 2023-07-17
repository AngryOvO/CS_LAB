#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_THREAD 20
/*
 * synchronyized problem ( 동기화 문제 )
 *
 * 스레드 20개 생성
 * 각 스레드는 메인의 count 주소값을 직접 포인팅해서 값을 100만큼 증가
 * 20개의 스레드가 하나의 주소공간을 동시에 사용
 * 예상하는 count의 값은 2000이어야 하지만 실제로 실행했을시
 * 값이 달라질 수가 있음
*/
void *t_func(void *data)
{
	int *count = (int *)data;
	int i;

	pthread_t thread_id = pthread_self();

	for(i = 0; i < 100; i++)
	{
		*count = *count + 1;
	}
}

int main(int argc, char**argv)
{
	pthread_t thread_id[MAX_THREAD];
	int i = 0;
	int count = 0;

	for(i = 0; i < MAX_THREAD; i++)
	{
		pthread_create(&thread_id[i], NULL, t_func,  (void *)&count);
	}

	for(i = 0; i < MAX_THREAD; i++)
	{
		pthread_join(thread_id[i], NULL);
	}

	printf("Main Tread : %d\n", count);
	return 0;
}




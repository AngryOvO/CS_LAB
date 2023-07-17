#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_THREAD 20
pthread_mutex_t m_lock;
/*
 * LOCK ( 동기화 문제의 해결법)
 *
 * 이전 동기화 문제에서 공유하는 자원을 동시에 사용하는 경우
 * 문제가 발생함
 *
 * 공유되는 자원을 사용하는 부분을 
 * critical section (크리티컬 섹션) 이라고 부름
 *
 * 동기화 문제라는 것은 크리티컬 섹션에 여러 개의 스레드나 프로세스가
 * 진입하는 경우
 *
 * 이를 해결하기위해 LOCK 방법
 * 간단하게 크리티컬 섹션에 하나의 프로세스나 스레드만 진입하게 하는 방법
 * 
 * 현재 예제
 * 스레드 20개 생성
 * 각 스레드는 메인의 count 주소값을 직접 포인팅해서 값을 100만큼 증가
 * 한 스레드가 크리티컬 섹션에 진입하면
 * 다른 스레드는 크리티컬 섹션에 진입한 스레드가 사용을 다 할 때 까지
 * 크리티컬 섹션에 진입 불가 >> LOCK이 걸려있는 상태
 * 그러므로
 * 예상한 결과와  실제 실행시의 결과가 2000으로 항상 동일함
*/
void *t_func(void *data)
{
	int *count = (int *)data;
	int i;

	pthread_t thread_id = pthread_self();

	for(i = 0; i < 100; i++)
	{
		pthread_mutex_lock(&m_lock);
		//critical section
		*count = *count + 1;
		pthread_mutex_unlock(&m_lock);
	}
}

int main(int argc, char**argv)
{
	pthread_t thread_id[MAX_THREAD];
	int i = 0;
	int count = 0;

	if(pthread_mutex_init(&m_lock, NULL) != 0)
	{
		perror("Mutex Init failure");
		return 1;
	}


	for(i = 0; i < MAX_THREAD; i++)
	{
		pthread_create(&thread_id[i], NULL, t_func,  (void *)&count);
	}

	for(i = 0; i < MAX_THREAD; i++)
	{
		pthread_join(thread_id[i], NULL);
	}
	pthread_mutex_destroy(&m_lock);
	printf("Main Tread : %d\n", count);
	return 0;
}




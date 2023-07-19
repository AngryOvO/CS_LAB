#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#include <pthread.h>

#define MAXBUF 3

/* 생산자 - 소비자 문제 
 *
 * 생산자 - 버퍼에 특정 값을 계속 할당 ( 생산 )
 * 소비자 - 버퍼에서 값을 계속 읽음 ( 소비 )
 *
 * 각 생산자와 소비자는 서로 다른 스레드를 통해서
 * 동시에 버퍼에 접근하려 하기 때문에
 * 각 버퍼의 인덱스 값은 동기화의 문제가 발생할 수 있음
 *
 * 세마포어를 활용해서 동기화 문제를 해결해야함
 *
 * 아래의 예제는 버퍼의 크기가 3이고
 * 생산자는 1 ~ 10 사이의 서로다른 임의의 숫자를 채우고
 * 소비자는 버퍼에 들어간 숫자를 출력하면서 사용하는 방식으로 구현했다.
*/

int buf[MAXBUF];
int buf_fill = 0;
int buf_use = 0;

sem_t sema;
sem_t mutex;
sem_t sema2;

// 버퍼는 원형 큐의 형태로 구현
void put(int value)
{
	buf[buf_fill] = value;
	buf_fill = (buf_fill + 1) % MAXBUF; 
}

int get()
{
	int temp = buf[buf_use];
	buf_use = (buf_use + 1) % MAXBUF;

	return temp;
}

void *producer(void *data)
{
	int i;
	int *value = (int *)data;
	for(i = 0; i < 10; i++)
	{
		sem_wait(&sema); // 세마포어의 값을 감소 
		sem_wait(&mutex); // mutex semaphore == lock
		put(value[i]); // critical section
		sem_post(&mutex);
		sem_post(&sema2); // 세마포어의 값을 증가
	}
}

void *consumer(void *arg)
{
	int i;
	int value;
	for(i = 0; i < 10; i++)
	{
		sem_wait(&sema2);
		sem_wait(&mutex);
		value = get();
		sem_post(&mutex);
		sem_post(&sema);
		printf("buf_value : %d\n",value);
	}
}


int main(void)
{
	pthread_t prod;
	pthread_t cons;

	// 난수 생성
	int array[10] = {1,2,3,4,5,6,7,8,9,10}; 

	srand(time(NULL));

	int i;
	for(i = 10 - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}

	// 각 세마포어 초기화
	sem_init(&sema, 0, MAXBUF); // sema는 시작 값이 3 생산을 할 수록 값 감소
	sem_init(&sema2, 0, 0); // sema2는 시작 값이 0 생산을 할 수록 값 증가
	sem_init(&mutex, 0, 1); // mutex

	pthread_create(&prod, NULL, producer, (void *)array); // 스레드 생성
	pthread_create(&cons, NULL, consumer, NULL); // 스레드 생성

	// 각 스레드가 종료 할 때 까지 메인 스레드 대기
	pthread_join(prod,NULL);
	pthread_join(cons,NULL);
	
	// 스레드 종료 이후 세마포어 할당 해제
	sem_destroy(&sema);
	sem_destroy(&mutex);
	
	return 0;
}


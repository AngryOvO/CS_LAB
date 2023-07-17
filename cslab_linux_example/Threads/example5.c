#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/* wait과 signal을 통한 스레드 동기화 방법
 *
 * 한 스레드에게 wait을 걸게되면 대기 상태가 되어
 * signal이나 broadcast의 함수를 호출하기 전까지 대기를 하고 있고
 * 특정한 조건이 달성하기 전까지 대기 상태에 머물러 있으면서
 * 다른 스레드가 critical section에 진입하지 못하게 만들어
 * race condition 상태가 생기지 않아
 * 동기화 문제가 발생하지 않는다.
 * 대기 상태의 스레드는 조건을 충족시키는 작업을 수행하고
 * critical section을 사용한 후 unlock을 한다.
 * 
 * 아래 예제를 살펴보면
 * f 스레드 루틴이 실행되고
 * before wait이 출력된 후
 * mutex_lock을 걸게된 다음 cond_wait을 통해 대기 상태로 만든다.
 * 이후 main 스레드에서 sleep이 끝난 이후 cond_signal을 통해
 * 대기 상태의 f 스레드를 깨우고
 * f스레드는 after wait을 출력한후 unlock을 한 뒤 종료한다.
*/


pthread_mutex_t mut;
pthread_cond_t cond;

void *f(void *data)
{
	printf("before wait\n");
	pthread_mutex_lock(&mut);
	pthread_cond_wait(&cond, &mut);
	printf("after wait\n");
	pthread_mutex_unlock(&mut);

	return 0;
}


int main(int argc, char *argv[])
{
	int res = 0;
	res = pthread_mutex_init(&mut, NULL);
	res = pthread_cond_init(&cond, NULL);

	pthread_t pt;
	pthread_create(&pt, NULL, f, NULL);

	sleep(2);
	pthread_cond_signal(&cond);

	pthread_join(pt, NULL);

	pthread_mutex_destroy(&mut);
	pthread_cond_destroy(&cond);

	return 0;

}


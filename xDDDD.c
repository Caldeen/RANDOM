#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <err.h>



sem_t sem1;
sem_t sem2;

int main(){
int semid1,semid2;
sem_init(&sem1,3,1);
sem_init(&sem2,3,0);

	if(fork()==0)
		{
		while(1){
		sem_wait(&sem1);

		sleep(1);
		printf("Child proc\n");
		sem_post(&sem2);
		sem_getvalue(&sem2,&semid2);
		printf("Sem2: %d",semid2);
		
		}
		
		}
while(1){
	sem_getvalue(&sem2,&semid2);
	printf("Sem2: %d",semid2);
	sem_wait(&sem2);
	sleep(1);
	printf("Parent proc\n");
	sem_post(&sem1);
}


return 0;
}

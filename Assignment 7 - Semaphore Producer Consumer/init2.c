#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <sys/shm.h>

#define MUTEX 0
#define WRT 1

union semun{
	int val;
	struct semid_ds *buf;
	ushort array;
}arg;

void setsem(int semid,int semnum)
{
	arg.val=1;
	if(semctl(semid,semnum,SETVAL,arg)<0)
		printf("Error in setsem");
}

int main(int argc, char const *argv[])
{
	char ch;
	int semid,shmid;
	key_t key=1234;
	key_t key_s=5678;
	
	semid=semget(key,2,IPC_CREAT | 0666);
	printf("Semid of the semaphore created : %d\n",semid);

	shmid=shmget(key_s,sizeof(int)*2,IPC_CREAT | 0666);
	int* rc=(int*)shmat(shmid,NULL,0);

	*rc=0;
	*(rc+1)=0;

	setsem(semid,WRT);
	setsem(semid,MUTEX);
	printf("Initialized\n");

	return 0;
}
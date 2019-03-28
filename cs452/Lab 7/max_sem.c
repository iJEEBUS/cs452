#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 32767
int main()
{
	int semID;

	// create semaphore
	if ((semID = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600)) == -1)
	{
		perror("main: semget");
		exit(1);
	}


	print("Setting shared_mem")
	// try to init to max value (32767)
	if (semctl(semID, 0, SETVAL, MAX) == -1)
	{
		perror("main: semctl");
		exit(1);
	}
	// try to set the value to (max value + 1)
	if (semctl(semID, 0, SETVAL, (MAX+1)) == -1)
	{
		printf("ERROR");
		exit(1);
	}	

	// remove the semaphore
	if (semctl(semID, IPC_RMID, 0) < 0)
	{
		perror("cannot free up semaphore");
		exit(1);
	}
	return 0;
}

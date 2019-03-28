/**
 * The reader class for the cs452 writer-reader lab assignment.
 *
 * This program will wait until something is written to the shared memory location
 * by the writer program. Then the reader will go about reading and printing the 
 * string to the console.
 *
 * @author Ron Rounsifer
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#define FOO 4096

int main() 
{

	int shmId;
	char *shmPtr;
	int flag = FOO - 1;
	int length = FOO - 2;
	int quit = FOO -3;
	int running = 1;
	key_t mem_key;

	mem_key = ftok(".", 'a');
	if ((shmId = shmget(mem_key, FOO, S_IRUSR)) < 0)
	{
		perror("I can't get no....\n");
	}
	
	// attach to the memory location
	if ((shmPtr = shmat(shmId, NULL, 0)) == (void *) -1)
	{
		perror("I cannot attach\n");
	}

	while (running)
	{
			
		if (shmPtr[flag] == 1)
		{
			if (shmPtr[quit] == 1) // check quit condition
				running = 0;
			else
			{
				for (int i = 0; i < (int) shmPtr[length]; ++i)
				{
					printf("%c", shmPtr[i]);
				}
			}
			shmPtr[flag] = 0;
		}
	}

	// detach
	if (shmdt(shmPtr) == -1)
	{
		perror("Could not detach\n");
	}
	return 0;
}

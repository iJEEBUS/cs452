/***
 * The writer class for the cs452 writer-reader lab assigment. 
 *
 * This program will create a shared memory space, write a user inputted string
 * to the memory space, and wait for the string to be read by the reader program.
 *
 * When quit it entered, the quit flag is signaled so the readers can exit their 
 * loops gracefully before the writer program exits its loop to terminate 
 * gracefully.
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

int main() {

	int shmId;
	char *shmPtr;
	key_t mem_key;
	int flag = FOO - 1;
	int length = FOO - 2;
	int quit = FOO - 3;

	mem_key = ftok(".", 'a');
	// create the shared memorif ((shmId = shmget(IPC_PRIVATE, 4096)))
	if ((shmId = shmget(mem_key, FOO, IPC_CREAT | S_IRUSR | S_IWUSR)) < 0)
	{
		perror("I can't get no....\n");
	}

	// attach to the memory location 
	if ((shmPtr = shmat (shmId, 0, 0)) == (void *) -1) 
	{
		perror("I cannot attach\n");	
	}
	

	// accept user input
	char* input = malloc(sizeof(char) * FOO);
	int running = 1;

	shmPtr[quit] = 0;

	// continuously get user input
	while (running)
	{
		if (shmPtr[flag] == 0)
		{
			printf("Enter a word: ");
			fgets(input, FOO, stdin);
			printf("%s\n", input);
		
			// stop check
			if (strcmp(input, "quit\n") == 0)
			{

				free(input);
				shmPtr[quit] = 1;
				shmPtr[flag] = 1;
				running = 0;
			} else {	
			
				// write to the memory location
				for (int i = 0; i < strlen(input); i++)
				{
					shmPtr[i] = input[i];
				}
				shmPtr[length] = strlen(input);
				shmPtr[flag] = 1;	
			}
		}
	}
	// detach from memory
	if (shmdt(shmPtr) == -1) 
	{
		perror("Could not detach\n");
	}
	return 0;
}

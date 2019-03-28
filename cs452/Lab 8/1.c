/**
* Lab 8 - Q. 1 - GVSU
*
* Accepts a username input of any size.
*
* @author Ron Rounsifer	
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 16

int main () {
    unsigned char *username;
    username = malloc(SIZE);
    int index = 0;
    int size_of_username = SIZE; 
    printf ("Please input username: ");
    
    
    do {
	char c = fgetc(stdin);
	
	if (c == '\n')
		break;
	if (index == (size_of_username-1))
	{
		
		// copy the username to a buffer		
		unsigned char *buffer = malloc(size_of_username);
		int i = 0;
		while (i < size_of_username)
		{
			buffer[i] = username[i];
			i++;
		}
		
		// double username size
		username = malloc(size_of_username*2);
		
		// copy buffer back into username
		i = 0;
		while (i < size_of_username)
		{
			username[i] = buffer[i];
			i++;
		}	
		
		size_of_username = size_of_username * 2;
	}	
	
	username[index] = c;	
	index++;
		
	} while (1);
    printf ("you entered: %s\n", username);
    free (username);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define KB 1024
#define AMOUNT 65 
#define LOOP 1

int main()
{
    int count, *intPtr;

    long int i, j, dim = AMOUNT * KB;


    if ((intPtr = malloc(dim * dim * sizeof(int))) == 0) {
	    perror("totally out of space");
	    exit(1);
    }
    for (count = 1; count <= LOOP; count++)
	    for (i = 0; i < dim; i++)
	        for (j = 0; j < dim; j++)
		        intPtr[i * dim + j] = (i + j) % count;
			//intPtr[j * dim + i] = (i + j) % count;	
    free(intPtr);
    return 0;
}

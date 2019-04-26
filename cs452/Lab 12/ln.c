#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv)
{

	// create hard links
	if (argc == 3) {

		// make sure enough args have been given
		if (link(argv[1], argv[2]) < 0)
		{
			perror("Error creating hard link.");
			exit(1);
		}

	// create soft links
	} else if (argc == 4) {
		if (!strcmp(argv[1], "-s")) {
			if (symlink(argv[2], argv[3]) < 0)
			{
				perror("Error creating soft link.");
				exit(1);
			}
		} else {
			printf("Usage:\n./executable oldpath newpath\n./executable -s oldpath newpath");
			exit(1);
		}

	// handle formatting error
	} else {
		printf("Usage:\n./executable oldpath newpath\n./executable -s oldpath newpath");
		exit(1);
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    struct stat statBuf;
    int dir = 0;

    if (argc < 2) {
	printf("Usage: filename required\n");
	exit(1);
    }

    if (stat(argv[1], &statBuf) < 0) {
	perror("huh?  there is ");
	exit(1);
    }

    
    
    // check for directory
    if (S_ISREG(statBuf.st_mode))
        printf("\nNot a directory\n\n");
    else
    {
        printf("\nDirectory\n\n");
        dir = 1;
    }
    
    printf("File: %s\n", argv[1]);
    if (dir == 1)
        printf("Size: %lu         Blocks: %lu        IO Block: %lu directory\n", statBuf.st_size, statBuf.st_blocks, statBuf.st_blksize);
    else
        printf("Size: %lu         Blocks: %lu        IO Block: %lu regular file\n", statBuf.st_size, statBuf.st_blocks, statBuf.st_blksize);
     printf("value is: %u\n", statBuf.st_mode);

    printf("Device: %lu     Inode: %lu    Links: %lu\n", statBuf.st_dev, statBuf.st_ino, statBuf.st_nlink);
    printf("Uid: %u    Gid: %u\n", statBuf.st_uid, statBuf.st_gid);

    return 0;
}

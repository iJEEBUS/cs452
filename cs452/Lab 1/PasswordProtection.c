/***************************************************************************
 * A simple script that will allow the user to enter a password
 * without echoing it back to the terminal.
 * 
 * When ran, the terminal will disable its echo feature until the user
 * enters the correct passphrase. At this point, the echo feature will
 * be restored to normal.
 *
 *
 * @author Ron Rounsifer
 * @version 01.16.2018
 ***************************************************************************/
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 32
#define MAX 50


/***************************************************************************
 * The point of execution for the script.
 *
 *
 * This will obtain and store the default terminal parameters for the 
 * current terminal session before disabling echo to the terminal and
 * prompting the user for their passphrase. Upon entering the valid 
 * phrase, the phrase is printed to the terminal, echo is restored, and
 * it prompts the user to enter another passphrase (which should be visible).
 ***************************************************************************/
int main(){
  
  struct termios save, working_copy;
  char *pass;

  // Retrieve terminal settings and save copy
  tcgetattr(STDIN_FILENO, &working_copy);
  save = working_copy;

  // Disable echo an update terminal attributes
  printf("Disabling echo...\n");
  working_copy.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &working_copy);

  // Prompt for passphrase until the correct one is entered 
  do {
    pass = malloc(SIZE * sizeof(char));
    printf("Enter your passphrase: ");
    fgets(pass, MAX, stdin);
    printf("\nYou entered: %s\n", pass);
  } while (strcmp(pass, "restore echo\n") != 0);

    // Restore terminal settings
  if (strcmp(pass, "restore echo\n") == 0) {
    printf("Default behavior restored.\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &save);
  }

  printf("Enter your passphrase: ");
  fgets(pass, MAX, stdin);
  printf("Your entered: %s", pass);
  
  free(pass);

  return 0;
}

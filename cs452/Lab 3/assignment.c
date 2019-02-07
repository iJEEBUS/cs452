/******************************************************************************
 * Communicating Processes - Lab 3
 *
 * This program will create a child process by using the fork() method.
 * From here, the child will sleep between 1-5 seconds before sending either
 * a SIGUSR1 or SIGUSR2 signal to the parent process. If the parent receives 
 * a SIGINT (ctrl-c) signal, then the parent will gracefully kill the child 
 * by calling kill(pid, SIGTERM) before terminating the parent process by
 * calling exiti(0). 
 *
 * @author Ron Rounsifer
 * @version 0.02 (02.05.2019 - 02.04.2019)
 ******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sigHandler (int);

// process id of child
pid_t pid = -1;

/******************************************************************************
 * Main execution point of the program 
 ******************************************************************************/
int main () {

  // fork
  if ((pid = fork()) == 0) /* child process */
  { 
    int rand_int = 0;
    int time_to_sleep = 0;
    printf("spawned child PID# %d\n", getpid());
   

    // sleeps child for a random time between 1-5 seconds
    // sends a signal to the parent process (SIGUSR1 or SIGUSR2) 
    for(;;) 
    {
      rand_int = rand() (% 4) + 1;
      time_to_sleep = rand_int + 1;
      sleep(time_to_sleep);
      
      // send sigusr1 if even, sigusr2 if odd
      if ((rand_int % 2) == 0)
      {
        kill(getppid(), SIGUSR1);
      } else {
        kill(getppid(), SIGUSR2);
      }
    }
  }
  else /* parent process */
  {
    // have parent wait to receive signals from the child
    for(;;)
    {
      sleep(1);
      signal (SIGUSR1, sigHandler);
      signal (SIGUSR2, sigHandler);
      signal (SIGINT, sigHandler); 
      printf ("waiting...\n");
      pause();
    }
  }
  return 0;
}

/******************************************************************************
 * Signal handler
 *
 * Overwrites the default behavior of the SIGUSR1, SIGUSR2, and SIGTERM signals.
 ******************************************************************************/
void sigHandler (int sigNum)
{
  switch(sigNum)
  {
    case SIGUSR1:
      signal(SIGUSR1, sigHandler);
      printf("received a SIGUSR1 signal\n");
      break;
    case SIGUSR2:
      signal(SIGUSR1, sigHandler);
      printf("received a SIGUSR2 signal\n");
      break;
    default:
      printf(" received.\n");
      printf("That's it. I'm shutting you down...\n");
      kill(pid, SIGTERM);
      exit(0);
  }
  return;
 }

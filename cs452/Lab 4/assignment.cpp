#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <string>
#include <iostream>
#include <fcntl.h>

using namespace std; // not safe, but I'm lazy right now

/* method the thread will execute */
void *retrieve_file(void *arg);

/* signal handler for when ^C is passed */
void sig_handler(int);

/* global variables for exiting server and counting requests */
int serving = true;

/* counter for number of requests received */
int total_num_requests;

/* counter for number of threads that are currently spawned */
int num_threads = 0;

int main()
{
  /* set the stdin to be blocking */
  int saved_flags = fcntl(0, F_GETFL, 0);
  saved_flags &= ~O_NONBLOCK;
  fcntl(0, F_SETFL, saved_flags);
  
  /* status of the thread spawned */
  int status; 
  /* the actual thread */
  pthread_t thread;
  /* file name entered by user */
  string file;
  /* temp file location that is sent to the thread */
  string temp_file;
  /* buffer that can handle 100 threads */
  string file_buffer[100]; 
  /* counter of files that have been processed */
  int file_count = 0;

  // parent thread that handles incoming requests
  // exits when ^C is passed.
  while(serving)
  {
    signal(SIGINT, sig_handler);
    cout << "filename to access: ";
    getline(cin, file);
    file_buffer[file_count] = file;
    
    // create and execute retrieve_file function in its own thread 
    if ((status = pthread_create(&thread, NULL, retrieve_file, &file_buffer[file_count])) != 0) 
    {
      fprintf(stderr, "thread creation error %d: %s\n", status, strerror(status));
      exit(1);
    }

    // used to track file buffer index 
    file_count++;
    if (file_count == 100)
    {
      file_count = 0;
    }
  }
  // make sure stdin is set to blocking
  fcntl(0, F_SETFL, saved_flags);
  return 0;
}

void *retrieve_file(void *arg)
{
  string *filename = (string *)arg;
  total_num_requests++;
  // there is an 80% chance to sleep for 1 second,
  // 20% chance to sleep for 7-10 seconds
  int time_key = (rand() % 10) + 1;
  if (time_key <= 8)
  {
    sleep(1);
  } else {
    int time_to_sleep = (rand() % 3) + 7;	    
    sleep(time_to_sleep);
  } 
  cout << "\nFile accessed: " << *filename << endl;
  num_threads--;
  return NULL;
}


void sig_handler(int sigNum)
{
  // this catches the ^C interrupt
  if (sigNum == SIGINT)
  {
    cout << "\nNumber of requests served: " << total_num_requests << endl;
    // breaks out of loop for parent thread
    serving = false;
    int saved_flags = fcntl(0, F_GETFL, 0);
    saved_flags |= O_NONBLOCK;
    // set the stdin to non-blocking
    fcntl(0, F_SETFL, saved_flags);
  }
}

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <string>
#include <iostream>

using namespace std; // not safe, but I'm lazy right now

/* method the thread will execute */
void *retrieve_file(void *arg);

/* signal handler for when ^C is passed */
void sig_handler(int);

/* global variables for exiting server and counting requests */
int serving = true;
int total_num_requests;

int main()
{
  pthread_t thread;
  void *thread_result;
  int status;

  string file;

  // infinite loop that will exit when ^C is passed.
  while(serving)
  {
    signal(SIGINT, sig_handler);
    cout << "filename to access: ";
    getline(cin, file);
    
    // create and start the thread to search for the filename
    // entered by the user
    if ((status = pthread_create(&thread, NULL, retrieve_file, &file)) != 0) 
    {
      fprintf(stderr, "thread creation error %d: %s\n", status, strerror(status));
      exit(1);
    }

    // wait for the thread to terminate and then
    // get its return value
    if ((status = pthread_join(thread, &thread_result)) != 0)
    {
      fprintf(stderr, "join error %d: %s\n", status, strerror(status));
      exit(1);
    }
  }

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
  cout << "File accessed: " << *filename << endl;
  return NULL;
}


void sig_handler(int sigNum)
{
  // this catches the ^C interrupt
  if (sigNum == SIGINT)
  {
    cout << "\nServicing report: " << total_num_requests << endl;
    
    // TODO fix this so the server actually exits the loop
    serving = false;
  }
}
